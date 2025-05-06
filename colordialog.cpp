#include "mainwindow.h"
#include "canvasview.h"
#include "colordialog.h"
#include "ui_colordialog.h"
#include <QPixmap>

ColorDialog::ColorDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ColorDialog)
{
    ui->setupUi(this);
    red = 0;
    green = 0;
    blue = 0;
    newColor = QColor(red, green, blue);
    newColorString = newColor.name();
    currentLayer = currentLayer = qobject_cast<MainWindow*>(parent)->GetCanvas()->GetActiveLayer();
    currentBrush = currentLayer->GetCatBrush();
    qDebug() << QString("Current Brush Acquired");
    ui->colorPreview->setStyleSheet("QLabel {color : " + newColorString + "; background-color : " + newColorString  + "; }");
}

ColorDialog::~ColorDialog()
{
    delete ui;
}

void ColorDialog::on_redSlider_sliderMoved(int position)
{
    ui->redSpinBox->setValue(position);
    red = position;
    newColor = QColor(red, green, blue);
    newColorString = newColor.name();
    ui->colorPreview->setStyleSheet("QLabel {color : " + newColorString + "; background-color : " + newColorString  + "; }");
}


void ColorDialog::on_redSpinBox_valueChanged(int arg1)
{
    ui->redSlider->setSliderPosition(arg1);
    red = arg1;
    newColor = QColor(red, green, blue);
    newColorString = newColor.name();
    ui->colorPreview->setStyleSheet("QLabel {color : " + newColorString + "; background-color : " + newColorString  + "; }");
}


void ColorDialog::on_greenSlider_sliderMoved(int position)
{
    ui->greenSpinBox->setValue(position);
    green = position;
    newColor = QColor(red, green, blue);
    newColorString = newColor.name();
    ui->colorPreview->setStyleSheet("QLabel {color : " + newColorString + "; background-color : " + newColorString  + "; }");
}


void ColorDialog::on_greenSpinBox_valueChanged(int arg1)
{
    ui->greenSlider->setSliderPosition(arg1);
    green = arg1;
    newColor = QColor(red, green, blue);
    newColorString = newColor.name();
    ui->colorPreview->setStyleSheet("QLabel {color : " + newColorString + "; background-color : " + newColorString  + "; }");
}


void ColorDialog::on_blueSlider_sliderMoved(int position)
{
    ui->blueSpinBox->setValue(position);
    blue = position;
    newColor = QColor(red, green, blue);
    newColorString = newColor.name();
    ui->colorPreview->setStyleSheet("QLabel {color : " + newColorString + "; background-color : " + newColorString  + "; }");
}


void ColorDialog::on_blueSpinBox_valueChanged(int arg1)
{
    ui->blueSlider->setSliderPosition(arg1);
    blue = arg1;
    newColor = QColor(red, green, blue);
    newColorString = newColor.name();
    ui->colorPreview->setStyleSheet("QLabel {color : " + newColorString + "; background-color : " + newColorString  + "; }");
}


void ColorDialog::on_buttonBox_accepted()
{
    currentBrush->SetBrushColor(newColor);
    currentLayer->SetCatBrush(currentBrush);
}

