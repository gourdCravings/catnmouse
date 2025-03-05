#ifndef CATBRUSH_H
#define CATBRUSH_H

#include <QGraphicsPixmapItem>
#include <QBitmap>

class CatBrush : public QGraphicsPixmapItem
{
public:
    CatBrush(QString textureName=":/brush/textures/testtexture.png", int brushSize=100, QColor color = Qt::blue, QString name = "default");
    //CatBrush(const QPixmap &txt) : texture(txt) {};
    // getters
    int GetWidth() const { return brushWidth; }
    QPixmap GetTexture() const { return texture; }
    QColor GetColor() const { return brushColor; }
    QString GetName() const { return brushName; }
    // setters
    void SetTexture(QPixmap newTexture);
    void SetBrushWidth(int newBrushWidth);

private:
    QPixmap texture;
    int brushWidth = 1;
    QColor brushColor;
    QString brushName;

};

Q_DECLARE_METATYPE(CatBrush)

#endif // CATBRUSH_H
