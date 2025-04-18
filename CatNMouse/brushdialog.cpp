#include "brushdialog.h"
#include "ui_brushdialog.h"
#include <QDebug>

BrushDialog::BrushDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BrushDialog)
    , brushList(new QList<CatBrush*>)
{
    ui->setupUi(this);
    currentLayer = qobject_cast<MainWindow*>(parent)->GetCanvas()->GetActiveLayer();
    qDebug() << currentLayer->GetLayerName();
    //currentLayer = qobject_cast<CanvasLayer*>(qobject_cast<MainWindow*>(parent)->GetStack()->currentWidget());
    currentBrush = currentLayer->GetCatBrush();
    // populate brushList
    CatBrush *roundBrush = new CatBrush(":/brush/textures/circletexture.png", 5, Qt::red, "round");
    CatBrush *rakeBrush = new CatBrush(":/brush/textures/testtexture.png", 100, Qt::blue, "rake");
    brushList->append(roundBrush);
    brushList->append(rakeBrush);
    // populate listWidget
    for (int i = 0; i<brushList->count(); ++i)
    {
        CatBrush *brush = brushList->at(i);
        ui->listWidget->addItem(brush->GetName());
    }
}

BrushDialog::~BrushDialog()
{
    delete ui;
}

void BrushDialog::on_listWidget_clicked(const QModelIndex &index)
{
    currentBrush = brushList->at(index.row());
}


void BrushDialog::on_buttonBox_accepted()
{
    currentLayer->SetCatBrush(currentBrush);
}

