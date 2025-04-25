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
#include "brushdialog.h"
#include "canvaswidget.h"
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include "canvasview.h"

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
    QStackedLayout* GetStack() const { return stack; }

    CanvasLayer* GetCurrentLayer();
    CanvasView* GetCanvas();
    void SetCanvas(CanvasView* newCanvas);

protected:
    //void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_addLayerBtn_clicked();

    // void on_layerListW_itemPressed(QListWidgetItem *item);

    // void on_layerListW_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    // void on_layerListW_itemChanged(QListWidgetItem *item);

    void on_eraseButton_clicked();

    void on_brushButton_clicked();

    // void on_layerListView_pressed(const QModelIndex &index);

    void open();

    void on_lineButton_clicked();

    void on_widthSpin_valueChanged(int arg1);

    void on_colorSelectButton_clicked();

    void on_selectButton_clicked();

    void on_layerListView_clicked(const QModelIndex &index);

public slots:
    void UpdateStackOrder(const QList<CanvasLayer*> &newOrder);
    void OnLayerSelected(const QModelIndex &index, QModelIndex &prev);
    void OnWidthSpinChanged(int newWidth);
    void OnActiveLayerChanged(CanvasLayer* newActive);
private:
    Ui::MainWindow *ui;
    // CanvasLayer *canvasLayer;
    // stack/list
    QStackedLayout *stack;
    QList<CanvasLayer> *layerList;
    QGraphicsScene *scene;
    CanvasLayer *activeLayer;
    bool widthInitiated = false;
    //QStringListModel model;
    LayerModel *model;
    QSortFilterProxyModel *proxyModel;
    // line
    QAction *lineAction;
    // save
    QMenu *saveMenu;
    QMenu *fileMenu;
    QMenu *optionsMenu;
    QAction *openAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *brushWidthAct;
    QList<QAction*> saveActs;
    // QWidget *widget;
    // CanvasLayer *canvas;
    // QGraphicsView *canvasView;
    void SetupListView();
    bool SaveFile(const QByteArray &fileFormat);
    void CreateActions();
    void CreateMenus();
    void Save();

    void Erase();
};
#endif // MAINWINDOW_H
