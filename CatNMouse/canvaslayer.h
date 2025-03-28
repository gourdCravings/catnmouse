// base class 4 layers

#ifndef CANVASLAYER_H
#define CANVASLAYER_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QPen>
#include "catbrush.h"
#include <QPainter>
#include "selectiontool.h"

class CanvasLayer : public QWidget
{
    Q_OBJECT
public:
    CanvasLayer(QObject *parent = nullptr);
    //virtual ~CanvasLayer() {};
    // properties
    //void setPenColor(const QColor &newColor);
    //void setPenWidth(int newWidth);
    void setLayerIndex(int newIndex);
    void setErasing(bool isErasing);

    // getters
    //CatBrush catBrush; // making this public because GetCatBrush causes problems for some reason
    CatBrush* GetCatBrush() const { return catBrush;  }
    CatBrush* GetCatEraser() const { return catEraser; }
    QString GetLayerName() const { return layerName; }
    QImage GetImage() const { return image; }
    bool GetToggle() const { return erasing; }
    bool GetSelect() const { return selecting; }

    // setters
    void SetCatBrush(CatBrush *newCatBrush);
    void SetLayerName(QString name);
    void ToggleErasing() { this->erasing = !erasing; SwapBrushes(&catBrush, &catEraser); }
    void ToggleSelecting();
    void ToggleScribbling();

    void FillColor(QColor color);

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
    QGraphicsPathItem* drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);
    void SwapBrushes(CatBrush **brushA, CatBrush **brushB);

    // boolean hell
    bool modified = false;
    bool scribbling = true;
    bool oldScribbling = true;
    bool erasing = false;
    bool drawingLine = false;
    bool selecting = false;
    bool oldSelecting = false;

    // int myPenWidth = 100;
    int layerIndexP = 0;
    // QColor myPenColor = Qt::blue;
    QImage image;
    QPoint lastPoint;
    QPoint lineStartPoint;
    QPoint currentLineEnd; // line tool preview
    CatBrush *catBrush;
    CatBrush *catEraser;
    SelectionTool *selectTool = nullptr;
    QString layerName;
    QList<QGraphicsPathItem*> pixelList;
    // QPixmap myTexture = QPixmap(":/brush/textures/testtexture.png").scaledToWidth(myPenWidth);
    //QBrush myBrush = QBrush(myPenColor, myTexture);
    //QPen myPen = QPen(myBrush, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    //QPen myPen = QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
};

#endif // CANVASLAYER_H
