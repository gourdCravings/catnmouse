#include "canvaslayer.h"
#include "mainwindow.h"
#include "catbrush.h"
#include <QMouseEvent>
#include <QPainter>
#include <QCursor>
#include <QApplication>
#include <QMessageBox>

CanvasLayer::CanvasLayer(QObject *parent)
{
    setAttribute(Qt::WA_StaticContents);
    catBrush = new CatBrush();
    // // init image with current size
    // QSize initSize = size();
    // if (!initSize.isValid() || initSize.isEmpty())
    //     initSize = QSize(640, 480); // default size

    // image = QImage(initSize, QImage::Format_ARGB32);
    // image.fill(Qt::white); // let user decide this
}

void CanvasLayer::SetCatBrush(CatBrush *newCatBrush)
{
    catBrush = newCatBrush; // should set catBrush to newCatBrush, doesn't
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
    // QMessageBox::information(this, "Tool Info",
    //                          "TOOL STATUS: Scribbling - " + QString::number(scribbling) +
    //                              ", Drawing Line - " + QString::number(drawingLine) +
    //                              ", Eyedropper - " + QString::number(eyedropper));
    // show();
    if (event->button() == Qt::LeftButton && scribbling) {
        lastPoint = event->position().toPoint();
    }
    else if (event->button() == Qt::LeftButton && drawingLine)
    {
        lineStartPoint = event->position().toPoint();
    }
    else if (event->button() == Qt::LeftButton && eyedropper == true)
    {
        eyedropPoint = event->position().toPoint();
        QMessageBox::information(this, "Eyedropper Info",
                                 "The cursor is at (" + QString::number(eyedropPoint.x()) + ", " + QString::number(eyedropPoint.y()) + ")");

        show();
        colorSelected = image.pixel(eyedropPoint.x(), eyedropPoint.y());
        QMessageBox::information(this, "Eyedropper Info",
                                  "The color selected is R =" + QString::number(colorSelected.red()) + " B ="
                                      + QString::number(colorSelected.blue()) + " G =" + QString::number(colorSelected.green()));
        show();

        catBrush->SetBrushColor(colorSelected);

        QGuiApplication::restoreOverrideCursor();
        scribbling = true;
        drawingLine = false;
        eyedropper = false;
    }
}

void CanvasLayer::mouseMoveEvent(QMouseEvent *event)
{
    // future: change if/else if to switch statement
    if ((event->buttons() & Qt::LeftButton) && scribbling && erasing == false)
        drawLineTo(event->position().toPoint());
    else if ((event->buttons() & Qt::LeftButton) && drawingLine)
    {
        // update the currentLineEnd for preview
        currentLineEnd = event->position().toPoint();
        // trigger repaint so paintEvent shows preview
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
    }
    else if (drawingLine) {
        drawLineTo(event->position().toPoint());
        drawingLine = false; // reset line drawing mode
        scribbling = true;
    }
}

void CanvasLayer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);

    if (drawingLine && (QApplication::mouseButtons() & Qt::LeftButton))
    {
        painter.setPen(QPen(catBrush->GetColor(), catBrush->GetWidth(), Qt::DashLine)); // dashed line for preview
        painter.drawLine(lineStartPoint, mapFromGlobal(QCursor::pos())); // live preview
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

    // using bresenham's line algorithm for some simple interpolation
    // NOTE: update this to xiaolin wu's algorithm
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
    /*QPainter painter(&image);
    // get newPoint
    QPoint newPoint;
    // set newPoint to translation of endPoint
    // translate endPoint by half of texture width to the left
    newPoint.setX(endPoint.x() - (catBrush->GetTexture().width()/2));
    // translate endPoint by half of texture height to the top
    newPoint.setY(endPoint.y() - (catBrush->GetTexture().width()/2));
    // draw texture
    painter.drawPixmap(newPoint, catBrush->GetTexture());
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
    // lastPoint = endPoint;*/
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

void CanvasLayer::eyedropTool()
{
    scribbling = false;
    drawingLine = false;
    eyedropper = true;
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
