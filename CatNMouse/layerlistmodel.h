#ifndef LAYERLISTMODEL_H
#define LAYERLISTMODEL_H

#include <QAbstractListModel>
#include <QString>
#include <QList>

class LayerListModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit LayerListModel(QObject *parent = nullptr);

    // A simple structure for each layer item.
    struct LayerItem {
        QString name;
        bool visible;
    };

    // Basic QAbstractListModel implementations
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    // Custom method to add a new layer to the model.
    void addLayer(const QString &name);

private:
    QList<LayerItem> layers;
};

#endif // LAYERLISTMODEL_H
