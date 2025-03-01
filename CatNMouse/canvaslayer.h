// base class 4 layers

#ifndef CANVASLAYER_H
#define CANVASLAYER_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QPen>
#include "catbrush_OLD.h"
#include <QPainter>

class CanvasLayer : public QWidget
{
public:
    CanvasLayer(QWidget *parent = nullptr);

    // properties
    //void setPenColor(const QColor &newColor);
    //void setPenWidth(int newWidth);
    void setLayerIndex(int newIndex);
    void setErasing(bool isErasing);

    bool isModified() const { return modified; }
    //QColor penColor() const { return myPenColor; }
    //int penWidth() const { return myPenWidth; }
    int layerIndex() const { return layerIndexP; }

    // stuff for switching tools
    void lineTool(); // Activates the line drawing tool

    bool saveImage(const QString &fileName, const char *fileFormat);

public slots:
    void clearImage();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:

    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);

    bool modified = false;
    bool scribbling = true;
    bool erasing = false;
    bool drawingLine = false;
    int myPenWidth = 100;
    int layerIndexP = 0;
    QColor myPenColor = Qt::blue;
    QImage image;
    QPoint lastPoint;
    QPoint lineStartPoint;
    QPoint currentLineEnd; // line tool preview
    //CatBrush catBrush;
    QPixmap myTexture = QPixmap(":/brush/textures/testtexture.png").scaledToWidth(myPenWidth);
    //QBrush myBrush = QBrush(myPenColor, myTexture);
    //QPen myPen = QPen(myBrush, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    //QPen myPen = QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
};

#endif // CANVASLAYER_H
