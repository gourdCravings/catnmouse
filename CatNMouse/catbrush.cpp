#include "catbrush.h"

CatBrush::CatBrush()
{
    SetTexture(QPixmap(":/brush/textures/testtexture.png"));
}

void CatBrush::SetTexture(QPixmap newTexture)
{
    //QRect cropRect = QRegion(newTexture.createMaskFromColor(Qt::transparent)).boundingRect();
    //texture = newTexture.copy(cropRect).scaledToWidth(brushWidth, Qt::SmoothTransformation);
    texture = newTexture.scaledToWidth(brushWidth, Qt::SmoothTransformation);
    this->setPixmap(texture);
}
