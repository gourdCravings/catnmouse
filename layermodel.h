#ifndef LAYERMODEL_H
#define LAYERMODEL_H

#include <QAbstractListModel>
#include "canvaslayer.h"

class LayerModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit LayerModel(QObject *parent = nullptr);
    //QModelIndex index(int row, int column, const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    //int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    void AddLayer(CanvasLayer* newLayer);

    bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild);

    CanvasLayer* GetLayerAtIndex(int index) const;

signals:
    void LayersReordered(const QList<CanvasLayer*> &newOrder);

private:
    QList<CanvasLayer*> listData;
};

#endif // LAYERMODEL_H
