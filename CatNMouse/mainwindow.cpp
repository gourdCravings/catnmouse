#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , stack(new QStackedLayout(this))
{
    ui->setupUi(this);
    // set up stack
    stack->setStackingMode(QStackedLayout::StackAll);
    ui->canvasWidget->setLayout(stack);
    connect(ui->layerListW, SIGNAL(currentRowChanged(int)),
            stack, SLOT(setCurrentIndex(int)));


    // set up background layer
    CanvasLayer *backgroundLayer = new CanvasLayer(this);
    backgroundLayer->setPalette(Qt::white);
    backgroundLayer->setAutoFillBackground(true);
    stack->addWidget(backgroundLayer);
    ui->layerListW->addItem("Background");
    ui->layerListW->item(0)->setCheckState(Qt::Checked);
    ui->layerListW->setCurrentRow(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addLayerBtn_clicked()
{
    ui->addLayerBtn->setDisabled(true);
    CanvasLayer *newLayer = new CanvasLayer(this);
    stack->addWidget(newLayer);
    int layerNumber = ui->layerListW->count();
    ui->layerListW->addItem(QString("Layer %1").arg(layerNumber));
    ui->layerListW->item(layerNumber)->setCheckState(Qt::Checked);
    ui->layerListW->setCurrentRow(layerNumber);
    // ui->layerListW->sortItems(Qt::DescendingOrder); // no idea how to set this permanently otherwise i would instead of having it run every goddamn time
    // ^ if you switch this the row numbers change. so this is a future subclassing thing we'll deal with later,
    ui->addLayerBtn->setDisabled(false);
}


void MainWindow::on_layerListW_itemPressed(QListWidgetItem *item)
{
    ui->layerListW->setCurrentItem(item);
}

void MainWindow::on_layerListW_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    stack->setCurrentIndex(ui->layerListW->row(current));
}

// NOTE: this is. Specifically meant for checking if a layer has been unchecked/checked
// which is really odd, considering how this event is more... general?
// regardless -- fix this via QAbstractListModel subclass @ later date. this isn't about getting the most optimal possible code rn
// it's about it Running and Working
void MainWindow::on_layerListW_itemChanged(QListWidgetItem *item)
{
    // get layer
    int layerIndex = ui->layerListW->row(item);
    QWidget *checkedLayer = stack->widget(layerIndex); // invalid conversion error using CanvasLayer, fix with subclass at later date
    if (item->checkState() == Qt::Unchecked)
    {
        // hide layer
        checkedLayer->hide();
    } else {
        // show layer
        checkedLayer->show();
    }
}


void MainWindow::on_eraseButton_clicked()
{
    CanvasLayer currentLayer = stack->currentWidget();
    currentLayer.setErasing(true);
}

