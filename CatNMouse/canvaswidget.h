#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>

class CanvasWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CanvasWidget(QWidget *parent = nullptr);
    void SetWidth(int newWidth) { this->setFixedWidth(newWidth); }
    void SetHeight(int newHeight) { this->setFixedHeight(newHeight); }

signals:
};

#endif // CANVASWIDGET_H
