#include "canvaslayer.h"
#include <QMouseEvent>
#include <QPainter>
#include <QApplication>
#include <QGraphicsOpacityEffect>
#include <iostream>

CanvasLayer::CanvasLayer(QObject *parent)
{
    setAttribute(Qt::WA_StaticContents);
    catBrush = new CatBrush(":/brush/textures/circletexture.png", 5, Qt::red, "round");
    catEraser = new CatBrush(":/brush/textures/circletexture.png", 5, Qt::blue, "round");
    // // init image with current size
    // QSize initSize = size();
    // if (!initSize.isValid() || initSize.isEmpty())
    //     initSize = QSize(640, 480); // default size

    // image = QImage(initSize, QImage::Format_ARGB32);
    // image.fill(Qt::white); // let user decide this
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

void CanvasLayer::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (scribbling)
        {
            lastPoint = event->position().toPoint();
        }
        else if (drawingLine)
        {
            lineStartPoint = event->position().toPoint();
        }
        else if (selecting)
        {
            if (!selectTool) // build tool if it doesn't exist yet
            {
                selectTool = new SelectionTool(QRubberBand::Rectangle, this);
            }
            selectTool->SetOrigin(event->pos());
            selectTool->setGeometry(QRect(selectTool->GetOrigin(), QSize()));
            selectTool->show();
        }
    }
}

void CanvasLayer::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        if (scribbling)
        {
            drawLineTo(event->position().toPoint());
        }
        else if (drawingLine)
        {
            // update the currentLineEnd for preview
            currentLineEnd = event->position().toPoint();
            // trigger repaint so paintEvent shows preview
            update();
        }
        else if (selecting)
        {
            selectTool->setGeometry(QRect(selectTool->GetOrigin(), event->position().toPoint()).normalized());
        }
    }
}

void CanvasLayer::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        drawLineTo(event->position().toPoint());
    }
    else if (drawingLine) {
        drawLineTo(event->position().toPoint());
        drawingLine = false; // reset line drawing mode
        scribbling = true;
    }
    else if (selecting)
    {
        ToggleScribbling(); // find some way to call the last drawing tool used and set it to that instead
        selectTool->ReleaseStyle();
    }
}

void CanvasLayer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);

    if (QApplication::mouseButtons() & Qt::LeftButton)
    {
        if (drawingLine)
        {
            painter.setPen(QPen(catBrush->GetColor(), catBrush->GetWidth(), Qt::DashLine)); // dashed line for preview
            painter.drawLine(lineStartPoint, mapFromGlobal(QCursor::pos())); // live preview
        }
    }
}

void CanvasLayer::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
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
    resizeImage(&visibleImage, size());

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
    image = QImage(this->size(), QImage::Format_ARGB32);
    image.fill(Qt::white);
}
