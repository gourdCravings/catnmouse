#include "selectiontool.h"
#include <QStylePainter>
#include <QPen>
#include <QCursor>
#include <QDebug>
#include <QRect>

SelectionTool::SelectionTool(QRubberBand::Shape shape, QWidget *parent) : QRubberBand(shape, parent)
{
    BuildStyle(shape, Qt::blue, QColor(Qt::blue));
    pen.setWidth(5);
}

void SelectionTool::BuildStyle(QRubberBand::Shape shape, QColor border, QColor bg)
{

    style.shape = shape;
    outline = border;
    background = bg;
    if (background.alphaF() == 1.0)
    {
        background.setAlphaF(0.5);
    }
    pen.setColor(outline);

    // QPalette palette;
    // palette.setBrush(QPalette::Highlight, QBrush(Qt::blue));
    // style.palette = palette;

    // // replace w some kind of style implementation so we don't have to run this every time
    // this->setPalette(palette);
}

void SelectionTool::ReleaseStyle()
{
    QColor borderColor = Qt::gray;
    borderColor.setAlphaF(0.5);
    pen.setWidth(2);
    BuildStyle(style.shape, borderColor, Qt::transparent);
    pen.setStyle(Qt::DashLine);
    this->repaint();
}

void SelectionTool::paintEvent(QPaintEvent *event)
{
    //Q_UNUSED(pe);
    QStylePainter painter(this);
    QRect rect = event->rect();

    painter.setPen(pen);
    painter.setBrush(background);
    painter.drawRect(rect);
    // this->initStyleOption(&style);
    // painter.drawControl(QStyle::CE_RubberBand, style);
    // painter.end();
    // this->update();
}

// void SelectionTool::mouseReleaseEvent(QMouseEvent *event)
// {
//     QPalette palette;
//     palette.setBrush(QPalette::Highlight, QBrush(Qt::green));
//     style.palette = palette;
//     this->setPalette(palette);
//     this->initStyleOption(&style);
//     this->update();
//     this->show();
// }
