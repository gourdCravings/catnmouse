#include "canvasdialog.h"
#include "ui_canvasdialog.h"
#include <QDebug>
#include "mainwindow.h"

CanvasDialog::CanvasDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CanvasDialog)
{
    ui->setupUi(this);
    canvasWidget = qobject_cast<CanvasWidget*>(qobject_cast<MainWindow*>(parent)->GetCanvas());
}

CanvasDialog::~CanvasDialog()
{
    delete ui;
}

void CanvasDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    canvasWidth = ui->widthSpin->value();
    canvasHeight = ui->heightSpin->value();
    canvasWidget->SetHeight(canvasHeight);
    canvasWidget->SetWidth(canvasWidth);
}

