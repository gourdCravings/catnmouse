#ifndef CATBRUSH_H
#define CATBRUSH_H

#include <QGraphicsPixmapItem>
#include <QBitmap>

class CatBrush : public QGraphicsPixmapItem
{
public:
    CatBrush(QString textureName=":/brush/textures/testtexture.png", int brushSize=100, QColor color = Qt::blue);
    //CatBrush(const QPixmap &txt) : texture(txt) {};
    // getters
    int GetWidth() const { return brushWidth; }
    QPixmap GetTexture() const { return texture; }
    // setters
    void SetTexture(QPixmap newTexture);

private:
    QPixmap texture;
    int brushWidth;
    QColor brushColor;

};

#endif // CATBRUSH_H
