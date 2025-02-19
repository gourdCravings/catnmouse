#include "canvaslayer.h"
#include <QMouseEvent>
#include <QPainter>

CanvasLayer::CanvasLayer(QObject *parent)
{
    setAttribute(Qt::WA_StaticContents);
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
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->position().toPoint();
        scribbling = true;
    }
}

void CanvasLayer::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling && erasing == false)
        drawLineTo(event->position().toPoint());
    /*else if (erasing == true)
    {
        this->setPenColor(QColor(0, 0, 0, 0));
    }*/
}

void CanvasLayer::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        drawLineTo(event->position().toPoint());
        scribbling = false;
    }
}

void CanvasLayer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
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
    // get newPoint
    QPoint newPoint;
    // set newPoint to translation of endPoint
    // translate endPoint by half of texture width to the left
    newPoint.setX(endPoint.x() - (myTexture.width()/2));
    // translate endPoint by half of texture height to the top
    newPoint.setY(endPoint.y() - (myTexture.height()/2));
    // draw texture
    painter.drawPixmap(newPoint, myTexture);
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
