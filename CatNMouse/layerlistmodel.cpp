#include "layerlistmodel.h"

LayerListModel::LayerListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int LayerListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return layers.count();
}

QVariant LayerListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= layers.size())
        return QVariant();

    const LayerItem &item = layers.at(index.row());
    if (role == Qt::DisplayRole)
        return item.name;
    else if (role == Qt::CheckStateRole)
        return item.visible ? Qt::Checked : Qt::Unchecked;

    return QVariant();
}

bool LayerListModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid() || index.row() < 0 || index.row() >= layers.size())
        return false;

    if (role == Qt::CheckStateRole) {
        bool newState = (value.toInt() == Qt::Checked);
        layers[index.row()].visible = newState;
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags LayerListModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
}

void LayerListModel::addLayer(const QString &name) {
    beginInsertRows(QModelIndex(), layers.size(), layers.size());
    layers.append({name, true});
    endInsertRows();
}
