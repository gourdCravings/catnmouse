#include "canvasview.h"
#include <QDebug>

CanvasView::CanvasView(QWidget *parent)
    : QGraphicsView(parent)
{
    mScene = new QGraphicsScene(this);
    setScene(mScene);
}

void CanvasView::AddLayer(CanvasLayer *layer)
{

    if (!model)
    {
        qDebug() << "model is null";
        return;
    }
    layer->setPreferredWidth(this->width());
    layer->setPreferredHeight(this->height());
    mScene->addItem(layer);
    mScene->setActiveWindow(layer);
}

void CanvasView::SetModel(LayerModel *newModel)
{
    model = newModel;
}

CanvasLayer* CanvasView::GetActiveLayer() const
{
    CanvasLayer *activeLayer = dynamic_cast<CanvasLayer*>(mScene->activeWindow());
    foreach (QGraphicsItem *item, mScene->items()) {
        QGraphicsProxyWidget *w;
        if (w = qgraphicsitem_cast<QGraphicsProxyWidget *>(item)) {
            qDebug() << "smth here";
        }
    }
    qDebug() << "wweeeeeeeeeeeeeee";
    if (activeLayer != nullptr)
    {
        qDebug() << activeLayer->GetLayerName();
    }
    return activeLayer;
    // QList<QGraphicsItem*> selectedItems = mScene->selectedItems();
    // qDebug() << "this line works";
    // if (!selectedItems.isEmpty()) {
    //     return dynamic_cast<CanvasLayer*>(selectedItems.first());
    // }
    // return nullptr;
}

void CanvasView::SetActiveLayer(CanvasLayer* layer)
{
    mScene->setActiveWindow(layer);
}

