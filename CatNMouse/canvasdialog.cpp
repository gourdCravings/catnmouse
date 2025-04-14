#include "canvasdialog.h"
#include "ui_canvasdialog.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QApplication>
#include <QDebug>

CanvasDialog::CanvasDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CanvasDialog)
{
    ui->setupUi(this);
    canvasView = qobject_cast<MainWindow*>(parent)->GetCanvas();
    mainWindow = qobject_cast<MainWindow*>(parent);

}

CanvasDialog::~CanvasDialog()
{
    delete ui;
}


void CanvasDialog::on_buttonBox_accepted()
{
    canvasWidth = ui->widthSpin->value();
    canvasHeight = ui->heightSpin->value();
    // change size of canvasView
    canvasView->setMinimumSize(canvasWidth, canvasHeight);
    canvasView->setMaximumSize(canvasWidth, canvasHeight);
    canvasView->scene()->setSceneRect(0, 0, canvasWidth, canvasHeight);
}


void CanvasDialog::on_buttonBox_rejected()
{
    // does this quit the application? yes. is it because it crashes? ...yes
    this->parent()->~QObject();
}

