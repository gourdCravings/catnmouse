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
#include <QGraphicsWidget>
#include <QGraphicsSceneMouseEvent>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>

class CanvasLayer : public QGraphicsWidget
{
    Q_OBJECT
public:
    explicit CanvasLayer(QGraphicsItem *parent = nullptr);
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
    bool GetCheckClicked() const { return checkClicked; }

    // setters
    void SetCatBrush(CatBrush *newCatBrush);
    void SetLayerName(QString name);
    void ToggleErasing() {
        this->erasing = !erasing; std::swap(catBrush, catEraser);
    }
    void ToggleSelecting();
    void ToggleScribbling();
    void ToggleFilling() {filling = !filling;}
    void ToggleCheckClicked() { checkClicked = !checkClicked; }
    void setVisible(bool visible);

    void FillColor(QColor color);

    bool isModified() const { return modified; }
    //QColor penColor() const { return myPenColor; }
    //int penWidth() const { return myPenWidth; }
    int layerIndex() const { return layerIndexP; }

    // stuff for switching tools
    void lineTool(); // Activates the line drawing tool

    bool saveImage(const QString &fileName, const char *fileFormat);

    QString toString() const { return GetLayerName(); }

public slots:
    void clearImage();


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void resizeEvent(QGraphicsSceneResizeEvent *event) override;
    // void showEvent(QShowEvent *event) override;

private:
    void drawLineTo(const QPoint &endPoint);
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
    bool filling = false;
    bool checkClicked = false;

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
    QColor fillColor;
    // QPixmap myTexture = QPixmap(":/brush/textures/testtexture.png").scaledToWidth(myPenWidth);
    //QBrush myBrush = QBrush(myPenColor, myTexture);
    //QPen myPen = QPen(myBrush, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    //QPen myPen = QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
};

#endif // CANVASLAYER_H
