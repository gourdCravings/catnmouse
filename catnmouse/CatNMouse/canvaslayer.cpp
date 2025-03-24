#include "canvaslayer.h"
#include <QMouseEvent>
#include <QPainter>
#include <QApplication>
#include <cmath>

CanvasLayer::CanvasLayer(QObject *parent)
{
    setAttribute(Qt::WA_StaticContents);
    catBrush = new CatBrush(":/brush/textures/circletexture.png", 5, Qt::red, "round");
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
    if (event->button() == Qt::LeftButton && scribbling) {
        lastPoint = event->position().toPoint();
    }
    else if (event->button() == Qt::LeftButton && drawingLine)
    {
        lineStartPoint = event->position().toPoint();
    }
    else if (event->button() == Qt::LeftButton && drawingCurve)
    {
        // Cities: Skylines style 3-point curve
        if (curveState == 0) {
            // first click - set starting point
            lineStartPoint = event->position().toPoint();
            // also initialize control and end points
            controlPoint = lineStartPoint;
            currentLineEnd = lineStartPoint;
            curveState = 1; // move to next state
        }
        else if (curveState == 1) {
            // second click - set flex/control point
            controlPoint = event->position().toPoint();
            curveState = 2; // move to next state
        }
        else if (curveState == 2) {
            // third click - set end point and draw
            currentLineEnd = event->position().toPoint();
            drawCurveTo(currentLineEnd);
            curveState = 0; // reset state
            drawingCurve = false; 
            scribbling = true; // return to default drawing mode
        }
        update(); // update display after each click
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
    else if (drawingCurve) {
        // just show preview based on current mouse position without changing points
        // only update the preview for the current state
        if (curveState == 1) {
            controlPoint = event->position().toPoint();
        }
        else if (curveState == 2) {
            currentLineEnd = event->position().toPoint();
        }
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
    else if (event->button() == Qt::LeftButton && drawingLine) {
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
    else if (drawingCurve) {
        // preview based on current curve state
        painter.setPen(QPen(catBrush->GetColor(), catBrush->GetWidth(), Qt::DashLine));
        
        if (curveState >= 1) {
            // draw the starting point
            painter.setPen(QPen(Qt::blue, 6));
            painter.drawPoint(lineStartPoint);
            painter.setPen(QPen(catBrush->GetColor(), catBrush->GetWidth(), Qt::DashLine));
            
            // preview line from start to current position
            if (curveState == 1) {
                painter.drawLine(lineStartPoint, mapFromGlobal(QCursor::pos()));
            }
        }
        
        if (curveState >= 2) {
            // draw the control point
            painter.setPen(QPen(Qt::green, 6));
            painter.drawPoint(controlPoint);
            painter.setPen(QPen(catBrush->GetColor(), catBrush->GetWidth(), Qt::DashLine));
            
            // preview curved path
            QPainterPath path;
            path.moveTo(lineStartPoint);
            path.quadTo(controlPoint, mapFromGlobal(QCursor::pos()));
            painter.drawPath(path);
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
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    // using bresenham's line algorithm for some simple interpolation
    // NOTE: update this to xiaolin wu's algorithm
    QLineF line(lastPoint, endPoint);
    int steps = qMax(abs(line.dx()), abs(line.dy())); // determine number of steps needed

    for (int i = 0; i <= steps; ++i) {
        qreal t = static_cast<qreal>(i) / steps;
        if (!drawingLine == true)
        {
            QPoint interpolatedPoint = lastPoint * (1 - t) + endPoint * t;

            QPoint newPoint(interpolatedPoint.x() - (catBrush->GetTexture().width() / 2),
                            interpolatedPoint.y() - (catBrush->GetTexture().height() / 2));
            painter.drawPixmap(newPoint, catBrush->GetTexture());
        } else {
            QPoint interpolatedPoint = lineStartPoint * (1 - t) + endPoint * t;

            QPoint newPoint(interpolatedPoint.x() - (catBrush->GetTexture().width() / 2),
                            interpolatedPoint.y() - (catBrush->GetTexture().height() / 2));
            painter.drawPixmap(newPoint, catBrush->GetTexture());
        }
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
    drawingCurve = false;
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

void CanvasLayer::drawCurveTo(const QPoint &endPoint)
{
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
