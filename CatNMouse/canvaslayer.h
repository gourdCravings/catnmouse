// base class 4 layers

#ifndef CANVASLAYER_H
#define CANVASLAYER_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>

class CanvasLayer : public QWidget
{
public:
    CanvasLayer(QObject *parent = nullptr);

    // properties
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);

    bool isModified() const { return modified; }
    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }

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
    bool scribbling = false;
    int myPenWidth = 1;
    QColor myPenColor = Qt::blue;
    QImage image;
    QPoint lastPoint;
};

#endif // CANVASLAYER_H
