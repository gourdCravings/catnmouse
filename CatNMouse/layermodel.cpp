#include "layermodel.h"
#include <QDebug>

LayerModel::LayerModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

QVariant LayerModel::data(const QModelIndex &index, int role) const
{
    const CanvasLayer *layer = listData[index.row()];
    switch (role)
    {
    case Qt::DisplayRole:
        return layer->GetLayerName();
        break;
    case Qt::CheckStateRole:
        return layer->isVisible() ? Qt::Checked : Qt::Unchecked;
    default:
        return QVariant();
    }
}

Qt::ItemFlags LayerModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) |
           Qt::ItemIsEditable |
           Qt::ItemIsSelectable |
           Qt::ItemIsDragEnabled |
           Qt::ItemIsDropEnabled |
           Qt::ItemIsUserCheckable |
           Qt::ItemIsEnabled;
}


int LayerModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return listData.count();
}

// int LayerModel::columnCount(const QModelIndex &parent) const
// {
//     Q_UNUSED(parent);
//     return 0;
// }

void LayerModel::AddLayer(CanvasLayer *newLayer)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    listData << newLayer;
    endInsertRows();
    emit LayerAdded(newLayer);
}

bool LayerModel::moveRows(const QModelIndex &sourceParent, int sourceRow, int count,
                          const QModelIndex &destinationParent, int destinationRow)
{
    if (sourceRow == destinationRow)
        return false;

    beginMoveRows(sourceParent, sourceRow, sourceRow, destinationParent, destinationRow);
    CanvasLayer *layer = listData.takeAt(sourceRow);
    listData.insert(destinationRow, layer);
    endMoveRows();
    emit LayersReordered(listData);

    return true;
}

bool LayerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) return false;

    CanvasLayer *layer = listData.at(index.row());

    if (role == Qt::CheckStateRole) {
        bool checked = (value.toInt() == Qt::Checked);
        layer->setVisible(checked);
        emit dataChanged(index, index, {role});
        return true;
    }

    return false;
}

CanvasLayer* LayerModel::GetLayerAtIndex(int index) const
{
    if (index >= 0 && index < listData.size()) {
        return listData.at(index);
    }
    qDebug() << "ERROR: Layer at index does not exist.";
    return nullptr;
}

