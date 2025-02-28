#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QStackedLayout>
#include <QKeyEvent>
#include <QWidget>
#include <QListWidget>
#include "canvaslayer.h"
#include <QStringListModel>
#include "layermodel.h"
#include <QSortFilterProxyModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    //void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_addLayerBtn_clicked();

    // void on_layerListW_itemPressed(QListWidgetItem *item);

    // void on_layerListW_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    // void on_layerListW_itemChanged(QListWidgetItem *item);

    void on_eraseButton_clicked();

    void on_brushButton_clicked();

    void on_layerListView_pressed(const QModelIndex &index);

public slots:
    void UpdateStackOrder(const QList<CanvasLayer*> &newOrder);
    void OnLayerSelected(const QModelIndex &index);
private:
    void SetupListView();
    Ui::MainWindow *ui;
    // CanvasLayer *canvasLayer;
    QStackedLayout *stack;
    QList<CanvasLayer> *layerList;
    //QStringListModel model;
    LayerModel *model;
    QSortFilterProxyModel *proxyModel;
    // QWidget *widget;
    // CanvasLayer *canvas;
    // QGraphicsView *canvasView;
};
#endif // MAINWINDOW_H
