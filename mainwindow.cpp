#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "colordialog.h"
#include <QMessageBox>
#include <QStandardPaths>
#include <QFileDialog>
#include <QInputDialog>
#include <QImageWriter>
#include <QLabel>

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
    // set up listview
    SetupListView();
    connect(ui->layerListView->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &MainWindow::OnLayerSelected);
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

    // trying to setup the file saving shit
    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcut(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    fileMenu = menuBar()->addMenu(tr("&File"));

    CreateActions();
    CreateMenus();

    // create the line tool action and connect it to canvasLayer
    lineAction = new QAction(tr("Line Tool"), this);
    lineAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_L)); // Optional shortcut
    connect(lineAction, &QAction::triggered, backgroundLayer, &CanvasLayer::lineTool);

    // add to menu
    QMenu *toolsMenu = menuBar()->addMenu(tr("Tools"));
    toolsMenu->addAction(lineAction);
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
    // dialog
    // probably should make this its own method
    BrushDialog *brushDialog = new BrushDialog(this);
    brushDialog->setWindowModality(Qt::WindowModality::WindowModal);
    brushDialog->show();
    // if (currentLayer.GetCatBrush().GetTexture().toImage() == QImage(":/brush/textures/testtexture.png"))
    // {
    //     currentLayer.GetCatBrush.SetTexture(QPixmap(":/brush/textures/circletexture.png"));
    // }
}


void MainWindow::on_layerListView_pressed(const QModelIndex &index)
{
    OnLayerSelected(index);
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
    if (!index.isValid())
        return;

    QModelIndex sourceIndex = proxyModel->mapToSource(index);
    // get currentLayer info
    CanvasLayer *currentLayer = qobject_cast<CanvasLayer*>(stack->currentWidget());
    //int currentIndex = stack->indexOf(currentLayer);
    // get selectedLayer info
    CanvasLayer *selectedLayer = model->GetLayerAtIndex(sourceIndex.row());
    // if selectedlayer doesn't change, ignore rest of code
    if (!selectedLayer || selectedLayer == currentLayer)
        return;
    currentLayer->setEnabled(false);
    currentLayer->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    selectedLayer->setEnabled(true);
    selectedLayer->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    selectedLayer->setFocus();
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

void MainWindow::Save()
{
    QAction *action = qobject_cast<QAction*>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    SaveFile(fileFormat);
}

bool MainWindow::SaveFile(const QByteArray &fileFormat)
{
    QString initialPath = (QStandardPaths::writableLocation(QStandardPaths::PicturesLocation) + "/untitled" + fileFormat);

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                    initialPath,
                                                    tr("%1 Files (*.%2);;All Files (*)")
                                                        .arg(QString::fromLatin1(fileFormat.toUpper()))
                                                        .arg(QString::fromLatin1(fileFormat)));
    if (fileName.isEmpty())
        return false;
    CanvasLayer *currentLayer = qobject_cast<CanvasLayer*>(stack->currentWidget());
    return currentLayer->saveImage(fileName, fileFormat.constData());
}

void MainWindow::CreateActions()
{
    const QList<QByteArray> imageFormats = QImageWriter::supportedImageFormats();
    for (const QByteArray &format : imageFormats) {
        QString text = tr("%1...").arg(QString::fromLatin1(format).toUpper());

        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, &QAction::triggered, this, &MainWindow::Save);
        saveActs.append(action);
    }
}

void MainWindow::CreateMenus()
{
    saveMenu = new QMenu(tr("&Save As"), this);
    for (QAction *action : std::as_const(saveActs))
        saveMenu->addAction(action);

    // fileMenu was already created and added to the menu bar.
    // Clear its contents and add your actions.
    fileMenu->clear();
    fileMenu->addAction(openAct);
    fileMenu->addMenu(saveMenu);
}


void MainWindow::open()
{
    qDebug() << "open() is here!";
}

void MainWindow::on_lineButton_clicked()
{
    lineAction->activate(QAction::Trigger);
}


void MainWindow::on_colorSelectButton_clicked()
{
    ColorDialog *colorDialog = new ColorDialog(this);
    colorDialog->setWindowModality(Qt::WindowModality::WindowModal);
    colorDialog->show();
}




void MainWindow::on_eyedropButton_clicked()
{
    CanvasLayer currentLayer = stack->currentWidget();
    currentLayer.eyedropTool();
}

