// #ifndef CATBRUSH_H
// #define CATBRUSH_H

// #include <QPen>
// #include <QBrush>
// #include <QBitmap>

// class CatBrush : public QPen
// {
// public:
//     CatBrush();
//     QPen GetPen(); // returns CatBrush as QPen
//     QBrush GetBrush(); // returns CatBrush as QBrush
//     // getters
//     int GetWidth() const { return brushWidth; }
//     // setters
//     void SetTexture(QPixmap newTexture);
//     void SetBrushPos(QLineF line);

// protected:
//     QRect GetBoundingBox(QPixmap img); // gets bounding box for cropping texture
// private:
//     int brushWidth = 10;
//     QColor brushColor = Qt::blue;
//     QPixmap texture;
//     QBrush brush = QBrush();
// };

// #endif // CATBRUSH_H
