#ifndef MANGO_2D_LINE_UTIL_H_
#define MANGO_2D_LINE_UTIL_H_
#include <QLineF>
#include <QVector2D>
bool IsSameLine(QLineF line1, QLineF line2); 

QPointF GetSameLinesConnectedPoint(QLineF line1, QLineF line2);

bool IsPointInLine(QPointF point, QLineF line);

bool EqualVector2D(QVector2D vec1, QVector2D vec2);
#endif
