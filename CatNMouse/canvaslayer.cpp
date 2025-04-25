#include "canvaslayer.h"
#include <QMouseEvent>
#include <QPainter>
#include <QApplication>
#include <QGraphicsOpacityEffect>
#include <iostream>
#include <QTimer>

CanvasLayer::CanvasLayer(QGraphicsItem *parent)
: QGraphicsWidget(parent)
{
    //setAttribute(Qt::WA_StaticContents);
    catBrush = new CatBrush(":/brush/textures/circletexture.png", 5, Qt::red, "round");
    catEraser = new CatBrush(":/brush/textures/circletexture.png", 5, Qt::blue, "round");
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

void CanvasLayer::SetCatBrush(CatBrush *newCatBrush)
{
    //catBrush = newCatBrush; // should set catBrush to newCatBrush, doesn't
    std::swap(catBrush, newCatBrush);
}
/*void CanvasLayer::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

void CanvasLayer::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}*/

void CanvasLayer::clearImage()
{
    image.fill(QColor(0, 0, 0, 0));
    modified = true;
    update();
}

void CanvasLayer::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (scribbling)
        {
            lastPoint = event->pos().toPoint();
        }
        else if (drawingLine)
        {
            lineStartPoint = event->pos().toPoint();
        }
        else if (selecting)
        {
            if (!selectTool) // build tool if it doesn't exist yet
            {
                selectTool = new SelectionTool(QRubberBand::Rectangle, nullptr);
            }
            selectTool->SetOrigin(event->pos().toPoint());
            selectTool->setGeometry(QRect(selectTool->GetOrigin(), QSize()));
            selectTool->show();
        }
    }
}

void CanvasLayer::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        if (scribbling)
        {
            drawLineTo(event->pos().toPoint());
        }
        else if (drawingLine)
        {
            // update the currentLineEnd for preview
            currentLineEnd = event->pos().toPoint();
            // trigger repaint so paintEvent shows preview
            update();
        }
        else if (selecting)
        {
            selectTool->setGeometry(QRect(selectTool->GetOrigin(), event->pos().toPoint()).normalized());
        }
    }
}

void CanvasLayer::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        drawLineTo(event->pos().toPoint());
    }
    else if (drawingLine) {
        drawLineTo(event->pos().toPoint());
        drawingLine = false; // reset line drawing mode
        scribbling = true;
    }
    else if (selecting)
    {
        ToggleScribbling(); // find some way to call the last drawing tool used and set it to that instead
        selectTool->ReleaseStyle();
    }
}

void CanvasLayer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QRectF dirtyRect = option->rect; // Get the invalidated area

    // Draw the image onto the widget
    painter->drawImage(dirtyRect, image, dirtyRect);

    // Check if the left mouse button is pressed
    if (QApplication::mouseButtons() & Qt::LeftButton)
    {
        if (drawingLine)
        {
            painter->setPen(QPen(catBrush->GetColor(), catBrush->GetWidth(), Qt::DashLine)); // Dashed line for preview
            painter->drawLine(lineStartPoint, mapFromScene(QCursor::pos())); // Live preview
        }
    }
}


void CanvasLayer::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    // code's broken, fix later
    // if (this->width > image.width() || height() > image.height()) {
    //     int newWidth = qMax(width() + 128, image.width());
    //     int newHeight = qMax(height() + 128, image.height());
    //     resizeImage(&image, QSize(newWidth, newHeight));
    //     update();
    // }
    // QWidget::resizeEvent(event);
}

void CanvasLayer::drawLineTo(const QPoint &endPoint)
{
    // figure out why texture appears in corner of canvas
    // because it does???
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true); // setting in catbrush?
    if (this->erasing)
    {
        //painter.save();
        painter.setCompositionMode(QPainter::CompositionMode_DestinationOut);
    }
    if (selecting)
    {
        painter.setClipRect(selectTool->geometry());
    }
    else if (selecting  == false &&
               painter.hasClipping())
    {
        qDebug() << "aaaaaaaaaa";
        painter.setClipRect(image.rect());
        scribbling = true;
        qDebug() << "aaaaaaaaaa";
    }
    // using bresenham's line algorithm for some simple interpolation
    // NOTE: update this to xiaolin wu's algorithm
    // also turn this into a method please
    QLineF line(lastPoint, endPoint);
    int steps = qMax(abs(line.dx()), abs(line.dy())); // determine number of steps needed

    for (int i = 0; i <= steps; ++i) {
        qreal t = static_cast<qreal>(i) / steps;
        QPoint interpolatedPoint = lastPoint * (1 - t) + endPoint * t;

        QPoint newPoint(interpolatedPoint.x() - (catBrush->GetTexture().width() / 2),
                        interpolatedPoint.y() - (catBrush->GetTexture().height() / 2));

        painter.drawPixmap(newPoint, catBrush->GetTexture());
        // ^ find out how to do this with just catBrush instead of the GetTexture() result
        // possibly with some method in catBrush
        // so that brush settings other than the texture can work
    }
    lastPoint = endPoint;
    update();

    // if line mode is active and the left button is still held, draw preview
    if (drawingLine && (QApplication::mouseButtons() & Qt::LeftButton))
    {
        painter.setPen(QPen(catBrush->GetColor(), catBrush->GetWidth(), Qt::DashLine)); // or a different style
        painter.drawLine(lineStartPoint, currentLineEnd);
    }
    if (!drawingLine)
    {
        lastPoint = endPoint;
    }
    update();

}

void CanvasLayer::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_ARGB32);
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void CanvasLayer::setLayerIndex(int newIndex)
{
    layerIndexP = newIndex;
}

void CanvasLayer::setErasing(bool isErasing)
{
    erasing = isErasing;
}

void CanvasLayer::SetLayerName(QString name)
{
    layerName = name;
}

void CanvasLayer::lineTool()
{
    scribbling = false;
    drawingLine = true;
}

bool CanvasLayer::saveImage(const QString &fileName, const char *fileFormat)
{
    QImage visibleImage = image;
    // resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName, fileFormat)) {
        modified = false;
        return true;
    }
    return false;
}

void CanvasLayer::SwapBrushes(CatBrush **brushA, CatBrush **brushB)
{
    CatBrush *temp;

    temp = *brushA;
    *brushA = *brushB;
    *brushB = temp;
}

void CanvasLayer::ToggleSelecting()
{
    this->selecting = !selecting;
    if (selecting == true)
    {
        ToggleScribbling();
    } else
    {
        selectTool->hide();
        selectTool = nullptr;
    }
}

void CanvasLayer::ToggleScribbling()
{

    scribbling = !scribbling;
}

// currently fills entire canvas -- rework this as paint bucket tool
void CanvasLayer::FillColor(QColor color)
{
    filling = true;
    if (image.isNull())
    {
        image = QImage(this->preferredSize().toSize(), QImage::Format_ARGB32_Premultiplied);
        image.fill(color);
    }
    update();

    //QMetaObject::invokeMethod(this, "ToggleFilling", Qt::QueuedConnection);
    // image = QImage(this->size().toSize(), QImage::Format_ARGB32);
    // image.fill(Qt::white);
}
