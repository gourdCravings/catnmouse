#ifndef BRUSHDIALOG_H
#define BRUSHDIALOG_H

#include <QDialog>
#include "catbrush.h"
#include "mainwindow.h"

namespace Ui {
class BrushDialog;
}

class BrushDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BrushDialog(QWidget *parent = nullptr);
    ~BrushDialog();

private slots:
    void on_listWidget_clicked(const QModelIndex &index);

    void on_buttonBox_accepted();

private:
    Ui::BrushDialog *ui;
    QList<CatBrush*> *brushList; // NOTE: possibly remake to QAbstractListModel like layers?
    CatBrush *currentBrush;
    CanvasLayer *currentLayer;
};

#endif // BRUSHDIALOG_H
