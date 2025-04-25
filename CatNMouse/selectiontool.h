#ifndef SELECTIONTOOL_H
#define SELECTIONTOOL_H

#include <QObject>
#include <QRubberBand>
#include <QStyleOption>
#include <QPainter>
#include <QColor>
#include <QPaintEvent>

class SelectionTool : public QRubberBand
{
    Q_OBJECT
public:
    SelectionTool(QRubberBand::Shape shape, QWidget *parent = nullptr);
    void SetOrigin(QPoint newPoint) { origin = newPoint; }
    QPoint GetOrigin() { return origin; }
    void ReleaseStyle();
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    void BuildStyle(QRubberBand::Shape shape, QColor border, QColor bg);

    // style stuff
    QColor outline;
    QColor background;
    QStyleOptionRubberBand style;
    QPen pen;
    QPoint origin;
};

#endif // SELECTIONTOOL_H
