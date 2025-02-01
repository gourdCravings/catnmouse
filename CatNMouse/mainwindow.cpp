// main window

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStackedLayout>
#include <QKeyEvent>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , canvasLayer(new CanvasLayer(this))
    , stack(new QStackedLayout(this))
    , widget(new QWidget(this))
    // , canvas(new CanvasLayer(this))
    // , canvasView(new QGraphicsView(this))
{
    ui->setupUi(this);
    CanvasLayer *layerOne = new CanvasLayer(this);
    CanvasLayer *layerTwo = new CanvasLayer(this);
    stack->addWidget(layerOne);
    stack->addWidget(layerTwo);
    stack->setStackingMode(QStackedLayout::StackAll);
    //CanvasLayer canvas = new CanvasLayer(QSize(500, 500));
    setCentralWidget(widget);
    centralWidget()->setLayout(stack);
    resize(500, 500);
    // canvasView->setScene(canvas);
    // setCentralWidget(canvasView);
    // canvasView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
    {
        bool index = stack->currentIndex();
        stack->setCurrentIndex(!index);
        QMessageBox::information(this, "a", "set index");
    }
}
