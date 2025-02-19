#ifndef CATBRUSH_H
#define CATBRUSH_H

#include <QGraphicsPixmapItem>

class CatBrush : public QGraphicsPixmapItem
{
public:
    CatBrush();
    // setters
    void SetTexture(QPixmap newTexture);
    QPixmap texture;

private:
    int brushWidth = 10;
    QColor brushColor = Qt::blue;

};

#endif // CATBRUSH_H
