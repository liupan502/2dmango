#ifndef MANGO_2D_POLYGON_UTIL_H_
#define MANGO_2D_POLYGON_UTIL_H_
#include <QPointF>
#include <QLineF>
#include <vector>

bool IsCounterclockwisePolygon(std::vector<QPointF> polygon);

void PolygonFlipY(std::vector<QPointF>& polygon);

bool IsPointInPolygon(QPointF point, std::vector<QPointF> polygon);
#endif // !MANGO_2D_POLYGON_UTIL_H_

