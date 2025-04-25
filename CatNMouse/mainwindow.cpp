#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "colordialog.h"
#include "canvasdialog.h"
#include <QMessageBox>
#include <QStandardPaths>
#include <QFileDialog>
#include <QInputDialog>
#include <QImageWriter>
#include <QLabel>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , stack(new QStackedLayout(this))
    , model(new LayerModel(this))
    , proxyModel(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);

    CanvasDialog *canvasDialog = new CanvasDialog(this);
    canvasDialog->setWindowModality(Qt::WindowModality::ApplicationModal);
    canvasDialog->exec();

    // set up model
    model->sort(0, Qt::DescendingOrder);
    // set up listview
    SetupListView();
    // set up canvasView
    ui->canvasView->SetModel(model);
    connect(model, &LayerModel::LayerAdded, ui->canvasView, &CanvasView::AddLayer);
    //connect(ui->canvasView, &CanvasView::SetActiveLayer, this, &MainWindow::OnActiveLayerChanged);
    // set up background layer
    CanvasLayer *backgroundLayer = new CanvasLayer();
    model->AddLayer(backgroundLayer);
    QModelIndex firstIndex = model->index(0, 0);
    ui->layerListView->selectionModel()->setCurrentIndex(firstIndex, QItemSelectionModel::Select | QItemSelectionModel::Current);
    backgroundLayer->FillColor(Qt::white);
    // backgroundLayer->setPalette(Qt::white);
    // backgroundLayer->setAutoFillBackground(true);
    backgroundLayer->SetLayerName("Background");

    //stack->addWidget(backgroundLayer);
    // set up spinbox
    // connect(ui->canvasView, &CanvasView::ActiveLayerChanged,
    //         this, &MainWindow::OnActiveLayerChanged);
    on_layerListView_clicked(firstIndex);
    //OnLayerSelected(firstIndex, firstIndex);
    ui->widthSpin->setValue(backgroundLayer->GetCatBrush()->GetWidth());
    //ui->widthSpin->setValue(5);
    //ui->widthSpin->setValue(backgroundLayer->GetCatBrush()->GetWidth());
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
    CanvasLayer *newLayer = new CanvasLayer();
    // set newLayer size to backgroundLayer
    newLayer->setPreferredSize(model->GetData()[0]->preferredSize());
    newLayer->FillColor(Qt::transparent);
    newLayer->SetLayerName(QString("Layer %1").arg(model->rowCount()));
    //stack->addWidget(newLayer);
    model->AddLayer(newLayer);
    //scene->addWidget(newLayer);
    QModelIndex newIndex = model->index(model->rowCount() - 1, 0);
    QModelIndex proxyIndex = proxyModel->mapFromSource(newIndex);
    ui->layerListView->setCurrentIndex(proxyIndex);
    ui->layerListView->scrollTo(proxyIndex);
    on_layerListView_clicked(proxyIndex);
    //stack->setCurrentWidget(newLayer);
    ui->addLayerBtn->setDisabled(false);
}

void MainWindow::on_eraseButton_clicked()
{
    QModelIndex currentIndex = ui->layerListView->currentIndex();
    CanvasLayer *currentLayer = model->GetLayerAtIndex(currentIndex.row());
    currentLayer->ToggleErasing();
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


// void MainWindow::on_layerListView_pressed(const QModelIndex &index)
// {
//     OnLayerSelected(index);
// }

void MainWindow::UpdateStackOrder(const QList<CanvasLayer *> &newOrder)
{
    if (!ui->canvasView || !ui->canvasView->scene()) {
        return; // Safety check to avoid null pointer crashes
    }

    QGraphicsScene *scene = ui->canvasView->scene();

    // Remove all existing layers from the scene (find a more efficient way if needed)
    for (QGraphicsItem *item : scene->items()) {
        CanvasLayer *layer = dynamic_cast<CanvasLayer *>(item);
        if (layer) {
            scene->removeItem(layer);
        }
    }

    // Re-add layers in the new order and update stacking (Z-values)
    int zIndex = 0;
    for (CanvasLayer *layer : newOrder) {
        if (!scene->items().contains(layer)) {
            scene->addItem(layer); // Add back to scene if not present
        }
        layer->setZValue(zIndex++); // Stack in the given order
    }

    // Restore focus to the topmost layer (last in newOrder)
    if (!newOrder.isEmpty()) {
        newOrder.last()->setFocus();
    }
}


void MainWindow::OnLayerSelected(const QModelIndex &index, QModelIndex &prev)
{
    qDebug() << "current changed";
    ui->layerListView->setCurrentIndex(index);
    CanvasLayer *newActive = model->GetLayerAtIndex(index.row());
    qDebug() << index.row();
    qDebug() << newActive->GetLayerName();
    ui->canvasView->SetActiveLayer(newActive);
    // if (!index.isValid())
    //     return;

    // QModelIndex sourceIndex = proxyModel->mapToSource(index);
    // // get currentLayer info
    // QGraphicsItem *activeItem = scene->activeWindow();
    // QGraphicsProxyWidget *activeProxy = qgraphicsitem_cast<QGraphicsProxyWidget*>(activeItem);
    // CanvasLayer *currentLayer = activeProxy ? qobject_cast<CanvasLayer*>(activeProxy->widget()) : nullptr;
    // //QGraphicsProxyWidget *currentLayer = qgraphicsitem_cast<QGraphicsProxyWidget*>(scene->activeWindow());
    // //CanvasLayer *currentLayer = qobject_cast<CanvasLayer*>(stack->currentWidget());
    // //int currentIndex = stack->indexOf(currentLayer);
    // // get selectedLayer info
    // CanvasLayer *selectedLayer = model->GetLayerAtIndex(sourceIndex.row());
    // // if selectedlayer doesn't change, ignore rest of code
    // if (!selectedLayer || selectedLayer == currentLayer)
    //     return;
    // // disable current layer
    // if (currentLayer)
    // {
    //     currentLayer->setEnabled(false);
    //     currentLayer->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    // }

    // // enable selected layer
    // selectedLayer->setEnabled(true);
    // selectedLayer->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    // selectedLayer->setFocus();

    // // set selectedLayer as active window
    // QGraphicsProxyWidget *selectedProxy = nullptr;

    // // iterate thru scene items to find selectedLayer proxy
    // // there has GOT to be a better way to do this this is gnarly
    // for (QGraphicsItem *item : scene->items())
    // {
    //     QGraphicsProxyWidget *proxy = qgraphicsitem_cast<QGraphicsProxyWidget*>(item);
    //     if (proxy && proxy->widget() == qobject_cast<QWidget *>(selectedLayer)) {
    //         selectedProxy = proxy;
    //         break;
    //     }
    // }

    // if (selectedProxy) {
    //     scene->setActiveWindow(selectedProxy);
    // }
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

CanvasLayer* MainWindow::GetCurrentLayer()
{
    return qobject_cast<CanvasLayer*>(scene->activeWindow());
}

void MainWindow::on_widthSpin_valueChanged(int arg1)
{
    if (widthInitiated == false)
    {
        widthInitiated = true;
        return;
    }
    // get current layer
    CanvasLayer *currentLayer = ui->canvasView->GetActiveLayer();
    qDebug() << currentLayer->isEmpty();
    // get catbrush
    CatBrush *currentBrush = currentLayer->GetCatBrush();
    // fix & set catbrush
    currentBrush->SetWidth(arg1);
    currentLayer->SetCatBrush(currentBrush);
    // // get current layer
    // CanvasLayer *currentLayer = qobject_cast<CanvasLayer*>(stack->currentWidget());

    // // get value from spinbox
    // int newValue = ui->widthSpin->value();

    // // get catbrush
    // CatBrush *currentBrush = currentLayer->GetCatBrush();

    // // fix & set catbrush
    // currentBrush->SetWidth(arg1);
    // currentLayer->SetCatBrush(currentBrush);
}

void MainWindow::OnWidthSpinChanged(int newWidth)
{
    CanvasLayer* activeLayer = ui->canvasView->GetActiveLayer();
    if (activeLayer)
    {
        CatBrush* brush = activeLayer->GetCatBrush();
        if (brush)
        {
            brush->SetWidth(newWidth);
        }
    }
}

void MainWindow::on_colorSelectButton_clicked()
{
    ColorDialog *colorDialog = new ColorDialog(this);
    colorDialog->setWindowModality(Qt::WindowModality::WindowModal);
    colorDialog->show();
}

void MainWindow::on_selectButton_clicked()
{
    // get current layer
    CanvasLayer *currentLayer = qobject_cast<CanvasLayer*>(stack->currentWidget());
    // toggle selection
    currentLayer->ToggleSelecting();
}

CanvasView* MainWindow::GetCanvas()
{
    return ui->canvasView;
}

void MainWindow::SetCanvas(CanvasView* newCanvas)
{
    ui->canvasView = newCanvas;
}

void MainWindow::OnActiveLayerChanged(CanvasLayer* newActive)
{
    int layerIndex = model->GetData().indexOf(newActive);
    if (layerIndex == -1)
    {
        qDebug() << "ERROR: newActive doesn't exist in list.";
    }
    else
    {
        ui->canvasView->SetActiveLayer(newActive);
    }

    // ^add check to confirm that newActive is actually in the damn list
}

void MainWindow::on_layerListView_clicked(const QModelIndex &index)
{
    int intDex = model->rowCount() - index.row() - 1;
    qDebug() << intDex;
    CanvasLayer* currentLayer = ui->canvasView->GetActiveLayer();
    if (currentLayer)
    {
        qDebug() << currentLayer->GetLayerName();
    }
    CanvasLayer* selectedLayer = model->GetData()[intDex];
    qDebug() << selectedLayer->GetLayerName();
    ui->canvasView->SetActiveLayer(selectedLayer);
}

