#include "canvaslayer.h"
#include "mainwindow.h"
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
        firstMouseMove = true; // reset for this click
        if (firstDraw) {
            firstDraw = false;
        }
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
    if ((event->buttons() & Qt::LeftButton) && scribbling && erasing == false) {
        if (firstMouseMove) {
            // skip drawing on the first mouse move
            lastPoint = event->position().toPoint();
            firstMouseMove = false;
        } else {
            // normal drawing on the subsequent mouse moves
            drawLineTo(event->position().toPoint());
        }
    }
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
        // only draw if this wasn't just a click without movement
        if (!firstMouseMove) {
            drawLineTo(event->position().toPoint());
        } else {
            // if single click - draw a dot
            QPainter painter(&image);
            painter.setRenderHint(QPainter::Antialiasing, true);
            QPoint newPoint(lastPoint.x() - (catBrush->GetTexture().width() / 2),
                           lastPoint.y() - (catBrush->GetTexture().height() / 2));
            painter.drawPixmap(newPoint, catBrush->GetTexture());
            update();
        }
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
    // PLEASE WORK I FUCKING BEG (my begging paid off finally)
    if (firstDraw) {
        lastPoint = endPoint;
        firstDraw = false;
        return;
    }

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true); // setting in catbrush?
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    // stupid line tool fucking broke again
    QPoint startPoint = drawingLine ? lineStartPoint : lastPoint;

    // using xiaolin wu's line algorithm for anti-aliased lines
    QLineF line(startPoint, endPoint);
    int x0 = line.p1().x();
    int y0 = line.p1().y();
    int x1 = line.p2().x();
    int y1 = line.p2().y();
    
    // determine if the line is steep (slope > 1)
    // if it is, swap x and y coordinates
    bool steep = abs(y1 - y0) > abs(x1 - x0);
    
    if (steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }
    
    // make sure we are always drawing from left to right
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    
    // calculate the slope and other key variables
    float dx = x1 - x0;
    float dy = y1 - y0;
    float gradient = dy / dx;
    
    // handle the first endpoint
    // we are using partial opacity at the endpoints in order to reduce artifacts
    int xend = round(x0);
    float yend = y0 + gradient * (xend - x0);
    float xgap = 1 - (x0 + 0.5 - floor(x0 + 0.5)); // calculate opacity for the first endpoint
    int xpxl1 = xend;
    int ypxl1 = floor(yend);
    
    // draw the first endpoint with proper opacity
    if (steep) {
        // for steep lines, x and y are swapped
        QPoint newPoint(ypxl1 - (catBrush->GetTexture().width() / 2),
                       xpxl1 - (catBrush->GetTexture().height() / 2));
        painter.setOpacity((1 - (yend - floor(yend))) * xgap);
        painter.drawPixmap(newPoint, catBrush->GetTexture());
        
        newPoint = QPoint(ypxl1 + 1 - (catBrush->GetTexture().width() / 2),
                         xpxl1 - (catBrush->GetTexture().height() / 2));
        painter.setOpacity((yend - floor(yend)) * xgap);
        painter.drawPixmap(newPoint, catBrush->GetTexture());
    } else {
        // for shallow lines, coordinates remain normal
        QPoint newPoint(xpxl1 - (catBrush->GetTexture().width() / 2),
                       ypxl1 - (catBrush->GetTexture().height() / 2));
        painter.setOpacity((1 - (yend - floor(yend))) * xgap);
        painter.drawPixmap(newPoint, catBrush->GetTexture());
        
        newPoint = QPoint(xpxl1 - (catBrush->GetTexture().width() / 2),
                         ypxl1 + 1 - (catBrush->GetTexture().height() / 2));
        painter.setOpacity((yend - floor(yend)) * xgap);
        painter.drawPixmap(newPoint, catBrush->GetTexture());
    }
    
    // initialize the interpolated y coordinate
    float intery = yend + gradient;
    
    // handle second endpoint
    xend = round(x1);
    yend = y1 + gradient * (xend - x1);
    xgap = x1 + 0.5 - floor(x1 + 0.5);
    int xpxl2 = xend;
    int ypxl2 = floor(yend);
    
    // draw the second endpoint
    if (steep) {
        QPoint newPoint(ypxl2 - (catBrush->GetTexture().width() / 2),
                       xpxl2 - (catBrush->GetTexture().height() / 2));
        painter.setOpacity((1 - (yend - floor(yend))) * xgap);
        painter.drawPixmap(newPoint, catBrush->GetTexture());
        
        newPoint = QPoint(ypxl2 + 1 - (catBrush->GetTexture().width() / 2),
                         xpxl2 - (catBrush->GetTexture().height() / 2));
        painter.setOpacity((yend - floor(yend)) * xgap);
        painter.drawPixmap(newPoint, catBrush->GetTexture());
    } else {
        QPoint newPoint(xpxl2 - (catBrush->GetTexture().width() / 2),
                       ypxl2 - (catBrush->GetTexture().height() / 2));
        painter.setOpacity((1 - (yend - floor(yend))) * xgap);
        painter.drawPixmap(newPoint, catBrush->GetTexture());
        
        newPoint = QPoint(xpxl2 - (catBrush->GetTexture().width() / 2),
                         ypxl2 + 1 - (catBrush->GetTexture().height() / 2));
        painter.setOpacity((yend - floor(yend)) * xgap);
        painter.drawPixmap(newPoint, catBrush->GetTexture());
    }
    
    // main drawing loop - draw all points between the endpoints
    // for each x, draw two y pixels with appropriate opacity
    if (steep) {
        for (int x = xpxl1 + 1; x < xpxl2; x++) {
            // calculate the coverage of the two pixels straddling the line
            QPoint newPoint(floor(intery) - (catBrush->GetTexture().width() / 2),
                          x - (catBrush->GetTexture().height() / 2));
            painter.setOpacity(1 - (intery - floor(intery))); // main pixel opacity
            painter.drawPixmap(newPoint, catBrush->GetTexture());
            
            newPoint = QPoint(floor(intery) + 1 - (catBrush->GetTexture().width() / 2),
                            x - (catBrush->GetTexture().height() / 2));
            painter.setOpacity(intery - floor(intery)); // adjacent pixel opacity
            painter.drawPixmap(newPoint, catBrush->GetTexture());
            
            intery += gradient; // move to next point along the line
        }
    } else {
        for (int x = xpxl1 + 1; x < xpxl2; x++) {
            QPoint newPoint(x - (catBrush->GetTexture().width() / 2),
                          floor(intery) - (catBrush->GetTexture().height() / 2));
            painter.setOpacity(1 - (intery - floor(intery)));
            painter.drawPixmap(newPoint, catBrush->GetTexture());
            
            newPoint = QPoint(x - (catBrush->GetTexture().width() / 2),
                            floor(intery) + 1 - (catBrush->GetTexture().height() / 2));
            painter.setOpacity(intery - floor(intery));
            painter.drawPixmap(newPoint, catBrush->GetTexture());
            
            intery += gradient;
        }
    }

    // update the last point for the next segment
    lastPoint = endPoint;
    modified = true;
    update();

    // draw preview line if in line tool mode
    if (drawingLine && (QApplication::mouseButtons() & Qt::LeftButton))
    {
        painter.setPen(QPen(catBrush->GetColor(), catBrush->GetWidth(), Qt::DashLine));
        painter.drawLine(lineStartPoint, currentLineEnd);
    }
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
    // getting the main window to access all layers
    QWidget* parentWidget = this->parentWidget();
    while (parentWidget && !qobject_cast<MainWindow*>(parentWidget)) {
        parentWidget = parentWidget->parentWidget();
    }
    MainWindow* mainWindow = qobject_cast<MainWindow*>(parentWidget);

    // grab all the layers from the stack
    QStackedLayout* stack = mainWindow->GetStack();
    if (!stack) return false;

    // make a new image to composite all layers
    QImage compositeImage(size(), QImage::Format_ARGB32);
    compositeImage.fill(Qt::transparent);
    QPainter compositePainter(&compositeImage);
    
    // paint all the layers from bottom to top
    for (int i = 0; i < stack->count(); ++i) {
        CanvasLayer* layer = qobject_cast<CanvasLayer*>(stack->widget(i));
        if (layer && layer->isVisible()) {
            compositePainter.drawImage(0, 0, layer->image);
        }
    }
    
    // save the composited image
    if (compositeImage.save(fileName, fileFormat)) {
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
