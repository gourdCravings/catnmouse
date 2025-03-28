#ifndef CANVASDIALOG_H
#define CANVASDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include "canvaswidget.h"

namespace Ui {
class CanvasDialog;
}

class CanvasDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CanvasDialog(QWidget *parent = nullptr);
    ~CanvasDialog();
    int GetWidth() { return canvasWidth; }
    int GetHeight() { return canvasHeight; }

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::CanvasDialog *ui;
    int canvasWidth;
    int canvasHeight;
    CanvasWidget *canvasWidget;
};

#endif // CANVASDIALOG_H
