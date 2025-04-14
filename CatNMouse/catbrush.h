#ifndef CATBRUSH_H
#define CATBRUSH_H

#include <QGraphicsPixmapItem>
#include <QBitmap>
#include <QDebug>

class CatBrush : public QGraphicsPixmapItem
{
public:
    CatBrush(QString textureName=":/brush/textures/round.png", int brushSize=10, QColor color = Qt::blue, QString name = "default", bool isAliased = true, int opacity = 50);
    //CatBrush(const QPixmap &txt) : texture(txt) {};
    // getters
    int GetWidth() const { return brushWidth; }
    QPixmap GetTexture() const { return texture; }
    QColor GetColor() const { return brushColor; }
    QString GetName() const { return brushName; }
    bool GetAliasing() const { return antiAliasing; }
    int GetOpacity() const { return brushOpacity; }
    // setters
    void SetTexture(QString newPath);
    void SetTexture(QPixmap newTexture);
    // void SetBrush(CatBrush newBrush) { this = newBrush };
    void SetWidth(int newBrushWidth);
    void SetAliasing(bool newAlias);
    void SetOpacity(float opacity, QPixmap brushTexture);
    void SetBrushColor(QColor newBrushColor);

public slots:
    void WidthSlot(int newBrushWidth) { SetWidth(newBrushWidth); }
private:
    QString texturePath;
    QPixmap texture;
    int brushWidth;
    int brushOpacity;
    QColor brushColor;
    QString brushName;
    bool antiAliasing;
};

Q_DECLARE_METATYPE(CatBrush)

#endif // CATBRUSH_H
