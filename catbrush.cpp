#include "catbrush.h"
#include <QDebug>

CatBrush::CatBrush(QString textureName, int brushSize, QColor color, QString name)
{
    // set brushWidth
    brushWidth = brushSize;
    // set brushColor
    brushColor = color;
    // set texture
    SetTexture(QPixmap(textureName));
    // set name
    brushName = name;
}

void CatBrush::SetTexture(QPixmap newTexture)
{
    //QRect cropRect = QRegion(newTexture.createMaskFromColor(Qt::transparent)).boundingRect();
    //texture = newTexture.copy(cropRect).scaledToWidth(brushWidth, Qt::SmoothTransformation);
    texture = newTexture.scaledToWidth(brushWidth);
    this->setPixmap(texture);
    // color texture
    // get mask
    QBitmap textureMask = texture.mask();
    texture.fill(brushColor);
    texture.setMask(textureMask);
}

void CatBrush::SetBrushWidth(int newWidth){
    brushWidth = newWidth;
}
