#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QImageWriter>
#include <QDir>
#include <QFileDialog>

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
    canvasLayer = new CanvasLayer(this);
    canvasLayer->setPalette(Qt::white);
    canvasLayer->setAutoFillBackground(true);
    stack->addWidget(canvasLayer);
    ui->layerListW->addItem("Background");
    ui->layerListW->item(0)->setCheckState(Qt::Checked);
    ui->layerListW->setCurrentRow(0);

    // trying to setup the file saving shit
    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcut(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    fileMenu = menuBar()->addMenu(tr("&File"));

    createActions();
    createMenus();

    // create the line tool action and connect it to canvasLayer
    lineAction = new QAction(tr("Line Tool"), this);
    lineAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_L)); // Optional shortcut
    connect(lineAction, &QAction::triggered, canvasLayer, &CanvasLayer::lineTool);

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

void MainWindow::save()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}

void MainWindow::createActions()
{
    const QList<QByteArray> imageFormats = QImageWriter::supportedImageFormats();
    for (const QByteArray &format : imageFormats) {
        QString text = tr("%1...").arg(QString::fromLatin1(format).toUpper());

        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, &QAction::triggered, this, &MainWindow::save);
        saveAsActs.append(action);
    }
}

void MainWindow::createMenus()
{
    saveAsMenu = new QMenu(tr("&Save As"), this);
    for (QAction *action : std::as_const(saveAsActs))
        saveAsMenu->addAction(action);

    // fileMenu was already created and added to the menu bar.
    // Clear its contents and add your actions.
    fileMenu->clear();
    fileMenu->addAction(openAct);
    fileMenu->addMenu(saveAsMenu);
}

bool MainWindow::saveFile(const QByteArray &fileFormat)
{
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                    initialPath,
                                                    tr("%1 Files (*.%2);;All Files (*)")
                                                        .arg(QString::fromLatin1(fileFormat.toUpper()))
                                                        .arg(QString::fromLatin1(fileFormat)));
    if (fileName.isEmpty())
        return false;
    return canvasLayer->saveImage(fileName, fileFormat.constData());
}

void MainWindow::open()
{
    qDebug() << "open() is here!";
}

