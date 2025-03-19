// #include "catbrush_OLD.h"

// CatBrush::CatBrush()
// {
//     SetTexture(QPixmap(":/brush/textures/testtexture.png"));
// }

// QPen CatBrush::GetPen() {
//     // initialize brush
//     brush = GetBrush();
//     // create pen
//     QPen pen = QPen();
//     pen.setWidth(brushWidth);
//     //pen.setCapStyle(Qt::RoundCap);
//     pen.setJoinStyle(Qt::RoundJoin);
//     pen.setBrush(brush);
//     // return pen
//     return pen;
// }

// QBrush CatBrush::GetBrush()
// {
//     // initialize brush
//     brush.setTexture(texture);
//     brush.setStyle(Qt::TexturePattern);
//     brush.setColor(brushColor);
//     return brush;
// }

// void CatBrush::SetBrushPos(QLineF line)
// {
//     // create transform
//     QTransform transform;
//     // translate
//     //transform.translate(line.dx(), line.dy());
//     // rotate
//     //transform.rotate(line.angle());
//     //transform.rotate((angle + oldAngle)/2);
//     //brush.setTransform(transform);
// }

// void CatBrush::SetTexture(QPixmap newTexture)
// {
//     QRect cropRect = QRegion(newTexture.createMaskFromColor(Qt::transparent)).boundingRect();
//     texture = newTexture.copy(cropRect).scaledToWidth(brushWidth, Qt::SmoothTransformation);
// }

// /*QRect CatBrush::GetBoundingBox(QPixmap img)
// {
//     // height & width of texture
//     int textX = img.width();
//     int textY = img.height();
//     // height & width of bounding box
//     int cropX = 0;
//     int cropY = 0;

//     // row-wise data addressing time
//     for (int y = 0; y < textY; ++cropY)
//     {
//         QRgb *row = (QRgb*)img.scanLine(y);
//         bool rowFilled = false;
//         for (int x = 0; x < textY; ++x)
//         {
//             if (qAlpha(row[x]))
//             {
//                 rowFilled = true;
//                 cropX = std::max(cropX, x);
//                 if (textX > x)
//                 {
//                     textX = x;
//                     x = cropX; // to only search for new right bounds from here
//                 }
//             }
//         }
//         if (rowFilled)
//         {
//             textY = std::min(textY, y);
//             cropY = y;
//         }
//     }
//     QRect rect = QRect(cropX, cropY);
//     return rect;
// }*/
