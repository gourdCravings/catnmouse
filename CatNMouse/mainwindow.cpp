#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , stack(new QStackedLayout(this))
    , model(new LayerModel(this))
    , proxyModel(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);

    // set up stack
    stack->setStackingMode(QStackedLayout::StackAll);
    ui->canvasWidget->setLayout(stack);
    // set up model
    model->sort(0, Qt::DescendingOrder);
    connect(model, &LayerModel::LayersReordered, this, &MainWindow::UpdateStackOrder);
    connect(ui->layerListView->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &MainWindow::OnLayerSelected);
    // set up listview
    SetupListView();
    // connect(ui->layerListView, SIGNAL(currentRowChanged(int)),
    //         stack, SLOT(setCurrentIndex(int)));


    // set up background layer
    CanvasLayer *backgroundLayer = new CanvasLayer(this);
    backgroundLayer->setPalette(Qt::white);
    backgroundLayer->setAutoFillBackground(true);
    backgroundLayer->SetLayerName("Background");
    stack->addWidget(backgroundLayer);
    model->AddLayer(backgroundLayer);
    // ui->layerListW->addItem("Background");
    // ui->layerListW->item(0)->setCheckState(Qt::Checked);
    // ui->layerListW->setCurrentRow(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addLayerBtn_clicked()
{
    ui->addLayerBtn->setDisabled(true);
    CanvasLayer *newLayer = new CanvasLayer(this);
    newLayer->SetLayerName(QString("Layer %1").arg(model->rowCount()));
    stack->addWidget(newLayer);
    model->AddLayer(newLayer);
    QModelIndex newIndex = model->index(model->rowCount()- 1, 0);
    QModelIndex proxyIndex = proxyModel->mapFromSource(newIndex);
    ui->layerListView->setCurrentIndex(proxyIndex);
    ui->layerListView->scrollTo(proxyIndex);
    stack->setCurrentWidget(newLayer);
    ui->addLayerBtn->setDisabled(false);
}


// void MainWindow::on_layerListView_itemPressed(QListWidgetItem *item)
// {
//     ui->layerListW->setCurrentItem(item);
// }

// void MainWindow::on_layerListW_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
// {
//     stack->setCurrentIndex(ui->layerListW->row(current));
// }

// NOTE: this is. Specifically meant for checking if a layer has been unchecked/checked
// which is really odd, considering how this event is more... general?
// regardless -- fix this via QAbstractListModel subclass @ later date. this isn't about getting the most optimal possible code rn
// it's about it Running and Working
// void MainWindow::on_layerListW_itemChanged(QListWidgetItem *item)
// {
//     // get layer
//     int layerIndex = ui->layerListW->row(item);
//     QWidget *checkedLayer = stack->widget(layerIndex); // invalid conversion error using CanvasLayer, fix with subclass at later date
//     if (item->checkState() == Qt::Unchecked)
//     {
//         // hide layer
//         checkedLayer->hide();
//     } else {
//         // show layer
//         checkedLayer->show();
//     }
// }


void MainWindow::on_eraseButton_clicked()
{
    CanvasLayer currentLayer = stack->currentWidget();
    currentLayer.setErasing(true);
}


void MainWindow::on_brushButton_clicked()
{
    CanvasLayer *currentLayer = qobject_cast<CanvasLayer*>(stack->currentWidget());
    CatBrush *newBrush = new CatBrush(":/brush/textures/circletexture.png", 5, Qt::red);
    // ^ if you make this brush too small it stops being a circle and becomes Square
    currentLayer->SetCatBrush(newBrush);
    // if (currentLayer.GetCatBrush().GetTexture().toImage() == QImage(":/brush/textures/testtexture.png"))
    // {
    //     currentLayer.GetCatBrush.SetTexture(QPixmap(":/brush/textures/circletexture.png"));
    // }
}


void MainWindow::on_layerListView_pressed(const QModelIndex &index)
{
    QModelIndex sourceIndex = proxyModel->mapToSource(index);
    ui->layerListView->setCurrentIndex(index);
    stack->setCurrentWidget(model->GetLayerAtIndex(sourceIndex.row()));
}

void MainWindow::UpdateStackOrder(const QList<CanvasLayer *> &newOrder)
{
    stack->setCurrentWidget(nullptr); // temp remove focus 2 prevent glitches

    // remove widgets -- find more effective way than while loop?
    while (stack->count() > 0) {
        QWidget *widget = stack->widget(0);
        stack->removeWidget(widget);
    }
    for (CanvasLayer *layer : newOrder) {
        stack->addWidget(layer);
    }

    // restore last active widget (topmost layer)
    if (!newOrder.isEmpty()) {
        stack->setCurrentWidget(newOrder.last());
    }
}

void MainWindow::OnLayerSelected(const QModelIndex &index)
{
    QModelIndex sourceIndex = proxyModel->mapToSource(index);
    if (!index.isValid())
        return;
    CanvasLayer *selectedLayer = model->GetLayerAtIndex(sourceIndex.row());
    stack->setCurrentWidget(selectedLayer);
}

void MainWindow::SetupListView()
{
    proxyModel->setSourceModel(model);
    proxyModel->sort(0, Qt::DescendingOrder);
    ui->layerListView->setModel(proxyModel);

    // doesn't work
    ui->layerListView->setDragEnabled(true);
    ui->layerListView->setAcceptDrops(true);
    ui->layerListView->setDragDropMode(QAbstractItemView::InternalMove);
    ui->layerListView->setDropIndicatorShown(true);
}
