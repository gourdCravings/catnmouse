#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QStackedLayout>
#include <QKeyEvent>
#include <QWidget>
#include "canvaslayer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
    CanvasLayer *canvasLayer;
    QStackedLayout *stack;
    QWidget *widget;
    // CanvasLayer *canvas;
    // QGraphicsView *canvasView;
};
#endif // MAINWINDOW_H
