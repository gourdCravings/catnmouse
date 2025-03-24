#include "catbrush.h"
#include <QDebug>

CatBrush::CatBrush(QString textureName, int brushSize, QColor color, QString name)
{
    // set brushWidth
    brushWidth = brushSize;
    // set brushColor
    brushColor = color;
    // set texture
    SetTexture(textureName);
    // set name
    brushName = name;
}

void CatBrush::SetTexture(QString newPath)
{
    texturePath = newPath;
    QPixmap basePix = QPixmap(texturePath);

    // this code is meant to convert to QImage using 32-bit ARGB due to QPixmaps having
    // a 1-bit mask, where filling with brushColor leads to us having a solid interior,
    // yet hitting a hard 1-bit boundary.

    QImage img = basePix.scaled(brushWidth, brushWidth, Qt::IgnoreAspectRatio, Qt::SmoothTransformation).toImage().convertToFormat(QImage::Format_ARGB32);

    // tinting every pixel but preserving the alpha
    for (int y = 0; y < img.height(); ++y)
    {
        QRgb *line = reinterpret_cast<QRgb*>(img.scanLine(y));
        for (int x = 0; x < img.width(); ++x)
        {
            QColor oldPixel = QColor::fromRgba(line[x]);
            int alpha = oldPixel.alpha();

            // if alpha=0, remain transparent
            // otherwise, apply the brush color but keep the original alpha
            if (alpha > 0)
            {
                QColor tinted = brushColor;
                tinted.setAlpha(alpha);
                line[x] = tinted.rgba();
            }
        }
    }

    // converting back to QPixmap
    texture = QPixmap::fromImage(img);
    this->setPixmap(texture);
}

void CatBrush::SetBrushWidth(int newWidth)
{
    brushWidth = newWidth;
    SetTexture(texturePath);
}
