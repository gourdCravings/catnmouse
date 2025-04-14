#ifndef CANVASDIALOG_H
#define CANVASDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include "canvasview.h"
#include "mainwindow.h"

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
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::CanvasDialog *ui;
    int canvasWidth;
    int canvasHeight;
    CanvasView *canvasView;
    MainWindow *mainWindow;

};

#endif // CANVASDIALOG_H
