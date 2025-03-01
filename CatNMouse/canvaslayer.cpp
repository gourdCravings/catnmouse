#include "canvaslayer.h"
#include <QMouseEvent>
#include <QPainter>
#include <QApplication>

CanvasLayer::CanvasLayer(QWidget *parent)
{
    setAttribute(Qt::WA_StaticContents);
    // Initialize the image with the current size (or a default size)
    QSize initSize = size();
    if (!initSize.isValid() || initSize.isEmpty())
        initSize = QSize(640, 480);  // default size if needed

    image = QImage(initSize, QImage::Format_ARGB32);
    image.fill(Qt::white);

    // color texture
    // get mask
    QBitmap textureMask = myTexture.mask();
    myTexture.fill(myPenColor);
    myTexture.setMask(textureMask);
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
    if (event->button() == Qt::LeftButton && scribbling) {
        lastPoint = event->position().toPoint();
    } else if (event->button() == Qt::LeftButton && drawingLine){
        lineStartPoint = event->position().toPoint();
    }
}

void CanvasLayer::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling && erasing == false)
        drawLineTo(event->position().toPoint());
    else if ((event->buttons() & Qt::LeftButton) && drawingLine) {
        // Update the currentLineEnd for the preview
        currentLineEnd = event->position().toPoint();
        // Trigger a repaint so paintEvent shows the preview
        update();
    }
    /*else if (erasing == true)
    {
        this->setPenColor(QColor(0, 0, 0, 0));
    }*/
}

void CanvasLayer::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        drawLineTo(event->position().toPoint());
    } else if (drawingLine) {
        drawLineTo(event->position().toPoint());
        drawingLine = false;  // Reset line drawing mode
        scribbling = true;
    }
}

void CanvasLayer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);

    if (drawingLine && (QApplication::mouseButtons() & Qt::LeftButton)) {
        painter.setPen(QPen(myPenColor, myPenWidth, Qt::DashLine)); // Dashed line for preview
        painter.drawLine(lineStartPoint, mapFromGlobal(QCursor::pos())); // Live preview
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
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // using bresenham's line algorithm for some simple interpolation
    QLineF line(lastPoint, endPoint);
    int steps = qMax(abs(line.dx()), abs(line.dy())); // determine number of steps needed

    for (int i = 0; i <= steps; ++i) {
        qreal t = static_cast<qreal>(i) / steps;
        QPoint interpolatedPoint = lastPoint * (1 - t) + endPoint * t;

        QPoint newPoint(interpolatedPoint.x() - (myTexture.width() / 2),
                        interpolatedPoint.y() - (myTexture.height() / 2));

        painter.drawPixmap(newPoint, myTexture);
    }

    lastPoint = endPoint;
    update();

    // get newPoint
    //QPoint newPoint;
    // set newPoint to translation of endPoint
    // translate endPoint by half of texture width to the left
    //newPoint.setX(endPoint.x() - (myTexture.width()/2));
    // translate endPoint by half of texture height to the top
    //newPoint.setY(endPoint.y() - (myTexture.height()/2));
    // draw texture
    //painter.drawPixmap(newPoint, myTexture);

    // If line mode is active and the left button is still held, draw a preview
    if (drawingLine && (QApplication::mouseButtons() & Qt::LeftButton)) {
        painter.setPen(QPen(myPenColor, myPenWidth, Qt::DashLine)); // or a different style
        painter.drawLine(lineStartPoint, currentLineEnd);
    }

    if (!drawingLine)
    {
        lastPoint = endPoint;
    }

    update();
    // //painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    // //painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    // QLineF line = QLineF(lastPoint, endPoint);
    // // catBrush.SetBrushPos(line);
    // // painter.setPen(catBrush.GetPen());
    // // painter.setBrush(catBrush.GetBrush());
    // painter.drawPixmap(lastPoint, myTexture);
    // //painter.drawLine(lastPoint, endPoint);
    // modified = true;

    // int rad = (myPenWidth / 2) + 2;
    // update(QRect(lastPoint, endPoint).normalized()
    //             .adjusted(-rad, -rad, +rad, +rad));
    // lastPoint = endPoint;
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

