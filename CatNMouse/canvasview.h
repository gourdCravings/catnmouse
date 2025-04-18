#ifndef CANVASVIEW_H
#define CANVASVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include "layermodel.h"
#include <QDebug>
#include "canvaslayer.h"

class CanvasView : public QGraphicsView
{
    Q_OBJECT
public:

    CanvasView(QWidget *parent = nullptr);
    void SetModel(LayerModel *newModel);
    CanvasLayer* GetActiveLayer() const;
    void SetActiveLayer(CanvasLayer* layer);
    bool IsActiveLayer(CanvasLayer* layer);
signals:
    void ActiveLayerChanged(CanvasLayer* newLayer);
public slots:
    void AddLayer(CanvasLayer *layer);

    //void ChangeSize(int width, int height);
private:
    LayerModel *model = nullptr;
    QGraphicsScene *mScene;
    CanvasLayer* currentLayer = nullptr;
};

#endif // CANVASVIEW_H
