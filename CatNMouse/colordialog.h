#ifndef COLORDIALOG_H
#define COLORDIALOG_H

#include <QDialog>
#include <QColor>
#include "canvaslayer.h"
#include "catbrush.h"

namespace Ui {
class ColorDialog;
}

class ColorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ColorDialog(QWidget *parent = nullptr);
    ~ColorDialog();

private slots:
    void on_redSlider_sliderMoved(int position);

    void on_redSpinBox_valueChanged(int arg1);

    void on_greenSlider_sliderMoved(int position);

    void on_greenSpinBox_valueChanged(int arg1);

    void on_blueSlider_sliderMoved(int position);

    void on_blueSpinBox_valueChanged(int arg1);

    void on_buttonBox_accepted();

private:
    Ui::ColorDialog *ui;
    CatBrush *currentBrush;
    CanvasLayer *currentLayer;
    QColor newColor;
    QString newColorString;
    int red;
    int blue;
    int green;
};

#endif // COLORDIALOG_H
