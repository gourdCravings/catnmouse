#include "canvaslayer.h"
#include <QMouseEvent>
#include <QPainter>
#include <QApplication>
#include <QGraphicsOpacityEffect>
#include <iostream>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QCursor>
#include <QDebug>

CanvasLayer::CanvasLayer(QGraphicsItem *parent)
: QGraphicsWidget(parent)
{
    //setAttribute(Qt::WA_StaticContents);
    catBrush = new CatBrush(":/brush/textures/circletexture.png", 5, Qt::red, "round");
    catEraser = new CatBrush(":/brush/textures/circletexture.png", 5, Qt::blue, "round");
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsFocusable);
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
        else if (eyedropper)
        {
            eyedropPoint = event->pos().toPoint();

            colorSelected = image.pixel(eyedropPoint.x(), eyedropPoint.y());

            catBrush->SetBrushColor(colorSelected);

            QGuiApplication::restoreOverrideCursor();
        } else if (drawingCurve){
            // Cities: Skylines style 3-point curve
            QPoint clickPoint = event->pos().toPoint();
            
            if (curveState == 0) {
                // first click - set starting point
                lineStartPoint = clickPoint;
                
                // reset other points
                controlPoint = clickPoint;
                currentLineEnd = clickPoint;
                previewPoint = clickPoint;
                
                curveState = 1; // move to next state
                printf("This is curve state 1!");
                
            } else if (curveState == 1) {
                // second click - set flex/control point
                controlPoint = clickPoint;
                curveState = 2; // move to next state
                
            } else if (curveState == 2) {
                // third click - set end point and draw
                currentLineEnd = clickPoint;
                drawCurveTo(currentLineEnd);
                curveState = 0; // reset state
                drawingCurve = false;
                scribbling = true; // return to default drawing mode
            }
            update();
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
    
    // slways update preview point for curve tool regardless of button state
    if (drawingCurve) {
        previewPoint = event->pos();
        update();
    }
}

void CanvasLayer::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        drawLineTo(event->pos().toPoint());
    }
    else if (event->button() == Qt::LeftButton && drawingLine) {
        // trying to fix my line tool again because it keeps on fucking breaking :)))))
        QPoint tempLastPoint = lastPoint;  
        lastPoint = lineStartPoint;        
        drawLineTo(event->pos().toPoint()); 
        lastPoint = tempLastPoint;         
        
        drawingLine = false; // reset line drawing mode
        scribbling = true;
    }
    else if (eyedropper)
    {
        scribbling = true;
        drawingLine = false;
        eyedropper = false;
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
    QRectF dirtyRect = option->rect;
    painter->drawImage(dirtyRect, image, dirtyRect);

    painter->setRenderHint(QPainter::Antialiasing, true);
    
    // preview for line tool
    if (drawingLine && (QApplication::mouseButtons() & Qt::LeftButton))
    {
        painter->setPen(QPen(catBrush->GetColor(), catBrush->GetWidth(), Qt::DashLine));
        QPointF itemPt = mapFromScene(scene()->views().first()->mapToScene(
            scene()->views().first()->viewport()->mapFromGlobal(QCursor::pos())));
        painter->drawLine(lineStartPoint, itemPt);
    }
    // curve preview
    else if (drawingCurve) {
        // draw the initial point marker
        if (curveState >= 1) {
            painter->setBrush(catBrush->GetColor());
            painter->setPen(Qt::NoPen);
            painter->drawEllipse(lineStartPoint, 5, 5);
        }
        
        painter->setPen(QPen(catBrush->GetColor(), catBrush->GetWidth(), Qt::DashLine));
        
        // first stage - line from start to current position
        if (curveState == 1) {
            // get current mouse position if not dragging
            QPointF currentPos = previewPoint;
            if (currentPos.isNull()) {
                QPointF itemPt = mapFromScene(scene()->views().first()->mapToScene(
                    scene()->views().first()->viewport()->mapFromGlobal(QCursor::pos())));
                currentPos = itemPt;
            }
            painter->drawLine(lineStartPoint, currentPos);
        }
        // second stage - draw control point and curve
        else if (curveState == 2) {
            // draw control point marker
            painter->setBrush(QColor(255, 165, 0)); // Orange
            painter->setPen(Qt::NoPen);
            painter->drawEllipse(controlPoint, 5, 5);
            
            // draw handle lines (optional)
            painter->setPen(QPen(QColor(150, 150, 150), 1, Qt::DashLine));
            painter->drawLine(lineStartPoint, controlPoint);
            
            // get current mouse position if not dragging
            QPointF currentPos = previewPoint;
            if (currentPos.isNull()) {
                QPointF itemPt = mapFromScene(scene()->views().first()->mapToScene(
                    scene()->views().first()->viewport()->mapFromGlobal(QCursor::pos())));
                currentPos = itemPt;
            }
            painter->drawLine(controlPoint, currentPos);
            
            // draw the curve preview
            painter->setPen(QPen(catBrush->GetColor(), catBrush->GetWidth(), Qt::DashLine));
            QPainterPath path;
            path.moveTo(lineStartPoint);
            path.quadTo(controlPoint, currentPos);
            painter->drawPath(path);
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
    qDebug() << QString("Drawing on: %1").arg(layerName);

}

void CanvasLayer::drawCurveTo(const QPoint &endPoint) {
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    // quadratic bezier curve with three points
    QLineF line1(lineStartPoint, controlPoint);
    QLineF line2(controlPoint, endPoint);
    int steps = qMax(abs(line1.length()), abs(line2.length()));
    steps = qMax(steps, 50); // ensure enough points for a smooth curve

    for (int i = 0; i <= steps; ++i) {
        qreal t = static_cast<qreal>(i) / steps;

        // quadratic bezier formula: B(t) = (1-t)²P₀ + 2(1-t)tP₁ + t²P₂
        QPointF point = (1 - t) * (1 - t) * lineStartPoint +
                        2 * (1 - t) * t * controlPoint +
                        t * t * endPoint;

        QPoint newPoint(point.x() - (catBrush->GetTexture().width() / 2),
                        point.y() - (catBrush->GetTexture().height() / 2));
        painter.drawPixmap(newPoint, catBrush->GetTexture());
    }

    // update lastPoint to prevent connecting to this curve in future operations
    lastPoint = endPoint;

    modified = true;
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
    eyedropper = false;
}

void CanvasLayer::curveTool()
{
    scribbling = false;
    drawingLine = false;
    drawingCurve = true;
    curveState = 0; // reset to place starting point
    // reset all points to prevent connecting to previous points
    lastPoint = QPoint(0, 0);
    lineStartPoint = QPoint(0, 0);
    controlPoint = QPoint(0, 0);
    currentLineEnd = QPoint(0, 0);
    printf("HELP ME");
}

void CanvasLayer::eyedropTool()
{
    scribbling = false;
    drawingLine = false;
    eyedropper = true;
}

bool CanvasLayer::saveImage(const QString &fileName, const char *fileFormat)
{    
    // check if image is valid before attempting to save
    if (image.isNull()) {
        // create an empty image if none exists
        image = QImage(this->preferredSize().toSize(), QImage::Format_ARGB32_Premultiplied);
        image.fill(Qt::transparent);
        qDebug() << "Created new empty image for saving";
    }
    
    // check if fileName is valid
    if (fileName.isEmpty()) {
        qDebug() << "Error: Empty filename provided for saving";
        return false;
    }
    
    QImage visibleImage = image;
    
    // check fileFormat to avoid segfault with null pointer
    if (!fileFormat || strlen(fileFormat) == 0) {
        qDebug() << "Error: Invalid file format provided, defaulting to PNG";
        if (visibleImage.save(fileName, "PNG")) {
            modified = false;
            qDebug() << "Successfully saved image to" << fileName;
            return true;
        }
    } else if (visibleImage.save(fileName, fileFormat)) {
        modified = false;
        qDebug() << "Successfully saved image to" << fileName << "as" << fileFormat;
        return true;
    }
    
    qDebug() << "Failed to save image to" << fileName;
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
        // make sure selectTool exists before trying to hide it
        if (selectTool != nullptr) {
            selectTool->hide();
            selectTool = nullptr;

            scribbling = true;
        }
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

// void CanvasLayer::showEvent(QShowEvent *event)
// {
//     this->setEnabled(false);
// }

void CanvasLayer::setVisible(bool visible)
{
    ToggleCheckClicked();
    if (visible)
    {
        show();
    } else
    {
        hide();
    }
}
