#include "canvasview.h"
#include <QDebug>
#include <QObject>

CanvasView::CanvasView(QWidget *parent)
    : QGraphicsView(parent)
{
    mScene = new QGraphicsScene(this);
    mScene->setItemIndexMethod(QGraphicsScene::NoIndex);
    setScene(mScene);
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
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
    currentLayer = layer;
    SetActiveLayer(layer);
    CanvasLayer* temp = qgraphicsitem_cast<CanvasLayer*>(mScene->focusItem()); // nullptr for some reason idk why
    qDebug() << QString("current according to passed layer: %1").arg(layer->GetLayerName());
    qDebug() << QString("hasFocus: %1").arg(currentLayer->hasFocus());
    if (temp != nullptr)
    {
        qDebug() << QString("current according to mScene: %1").arg(temp->GetLayerName());
    } else {
        qDebug() << "temp is null";
    }
}

void CanvasView::SetModel(LayerModel *newModel)
{
    model = newModel;
}

CanvasLayer* CanvasView::GetActiveLayer() const
{
    // CanvasLayer *activeLayer = qgraphicsitem_cast<CanvasLayer*>(mScene->focusItem());
    if (currentLayer != nullptr)
    {
        qDebug() << QString("GetActiveLayer(): %1").arg(currentLayer->GetLayerName());
    } else
    {
        qDebug() << "nothin'";
    }
    return currentLayer;
}

void CanvasView::SetActiveLayer(CanvasLayer* layer)
{
    if (currentLayer)
    {
        currentLayer->ungrabMouse();
    }
    currentLayer = layer;
    currentLayer->grabMouse();
    currentLayer->setFocus();
    //qDebug() << QString("SetActiveLayer name: %1").arg(currentLayer->GetLayerName());
    //qDebug() << QString("SetActiveLayer enabled: %1").arg(layer->isEnabled());

    // foreach (QGraphicsItem* item, mScene->items())
    // {
    //     CanvasLayer* temp = qgraphicsitem_cast<CanvasLayer*>(item);
    //     qDebug() << QString("%1 is enabled: %2").arg(temp->GetLayerName()).arg(temp->isEnabled());
    // }
}

bool CanvasView::IsActiveLayer(CanvasLayer *layer)
{
    if (layer != currentLayer)
    {
        layer->setEnabled(false);
        return false;
    }
    return true;
}
