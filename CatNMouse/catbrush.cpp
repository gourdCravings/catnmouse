#include "catbrush.h"
#include <QDebug>
#include <QPainter>

CatBrush::CatBrush(QString textureName, int brushSize, QColor color, QString name, bool isAliased, int opacity)
{
    // set brushWidth
    brushWidth = brushSize;
    // set brushColor
    brushColor = color;
    // set brushOpacity
    brushOpacity = opacity;
    // set texture
    SetTexture(textureName);
    // set name
    brushName = name;
    // set antialiasing
    SetAliasing(isAliased);
    // qDebug() << QString("brushOpacity = %1").arg(brushOpacity);
}

void CatBrush::SetTexture(QString newPath)
{
    texturePath = newPath;
    QPixmap newTexture = QPixmap(texturePath);
    SetTexture(newTexture);

    // color texture
    // get mask
    //QBitmap textureMask = texture.mask();
}

void CatBrush::SetTexture(QPixmap newTexture)
{
    // set color
    QPainter texturePainter = QPainter(&newTexture);
    texturePainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    texturePainter.fillRect(newTexture.rect(), brushColor);

    // set opacity
    // texturePainter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    // texturePainter.fillRect(newTexture.rect(), QColor(0, 0, 0, brushOpacity));
    texturePainter.end();
    // // set opacity
    // SetOpacity(brushOpacity, newTexture);
    if (antiAliasing)
    {
        texture = newTexture.scaledToWidth(brushWidth, Qt::SmoothTransformation);
    } else
    {
        texture = newTexture.scaledToWidth(brushWidth, Qt::FastTransformation);
    }
    this->setPixmap(texture);
    // texture.fill(brushColor);
    // texture.setMask(textureMask);
}
// void CatBrush::SetTexture(QString newPath)
// {
//     texturePath = newPath;
//     QPixmap basePix = QPixmap(texturePath);

//     // this code is meant to convert to QImage using 32-bit ARGB due to QPixmaps having
//     // a 1-bit mask, where filling with brushColor leads to us having a solid interior,
//     // yet hitting a hard 1-bit boundary.

//     QImage img = basePix.scaled(brushWidth, brushWidth, Qt::IgnoreAspectRatio, Qt::SmoothTransformation).toImage().convertToFormat(QImage::Format_ARGB32);

//     // tinting every pixel but preserving the alpha
//     for (int y = 0; y < img.height(); ++y)
//     {
//         QRgb *line = reinterpret_cast<QRgb*>(img.scanLine(y));
//         for (int x = 0; x < img.width(); ++x)
//         {
//             QColor oldPixel = QColor::fromRgba(line[x]);
//             int alpha = oldPixel.alpha();

//             // if alpha=0, remain transparent
//             // otherwise, apply the brush color but keep the original alpha
//             if (alpha > 0)
//             {
//                 QColor tinted = brushColor;
//                 tinted.setAlpha(alpha);
//                 line[x] = tinted.rgba();
//             }
//         }
//     }

//     // converting back to QPixmap
//     texture = QPixmap::fromImage(img);
//     this->setPixmap(texture);
// }

void CatBrush::SetBrushWidth(int newWidth)
{
    brushWidth = newWidth;
    SetTexture(texturePath);
}

void CatBrush::SetAliasing(bool newAlias)
{
    antiAliasing = newAlias;
    if (antiAliasing)
    {
        this->setTransformationMode(Qt::SmoothTransformation);
    } else
    {
        this->setTransformationMode(Qt::FastTransformation);
    }
}

void CatBrush::SetOpacity(float opacity, QPixmap brushTexture)
{
    QPixmap opacityMap(brushTexture.size());
    opacityMap.fill(Qt::transparent);
    QPainter opacityPainter = QPainter(&opacityMap);
    opacityPainter.setCompositionMode(QPainter::CompositionMode_Source);
    opacityPainter.drawPixmap(0, 0, brushTexture);
    opacityPainter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    opacityPainter.fillRect(opacityMap.rect(), QColor(0, 0, 0, brushOpacity));
    opacityPainter.end();
    texture = opacityMap;
}

void CatBrush::SetBrushColor(QColor newColor) {
    brushColor = newColor;
    SetTexture(texturePath);
}

