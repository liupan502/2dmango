#ifndef MANGO_2D_LINE_UTIL_H_
#define MANGO_2D_LINE_UTIL_H_
#include <QLineF>
#include <QVector2D>
bool IsSameLine(QLineF line1, QLineF line2) {
  if (line1.isNull() || line2.isNull()) {
    return false;
  }
  QLineF unit_vector1 = line1.unitVector();
  QVector2D vec1 = QVector2D (unit_vector1.p1()-unit_vector1.p2());
  QLineF unit_vector2 = line2.unitVector();
  QVector2D vec2 = QVector2D(unit_vector2.p1() - unit_vector2.p2());
  if (vec1 != vec2 && vec1 != -vec2) {
    return false;
  }

  QVector2D vec3 = QVector2D(line1.p1() - line2.p1());
  QVector2D vec4 = QVector2D(line1.p1() - line2.p2());
  if (vec3.isNull() || vec4.isNull()) {
    return true;
  }
  vec3.normalize();
  vec4.normalize();
  if (vec3 == vec4 || vec3 == -vec4) {
    return true;
  }
  else {
    return false;
  }  
  
  return false;
}

QPointF GetSameLinesConnectedPoint(QLineF line1, QLineF line2) {
  std::vector<QPointF> points;
  points.push_back(line1.p1());
  points.push_back(line1.p2());
  points.push_back(line2.p1());
  points.push_back(line2.p2());
  for (int i = 0; i < points.size(); i++) {
    QPointF point1 = points[i];
    for (int j = i+1; j < points.size(); j++) {
      QPointF point2 = points[j];
      if (point1.x() > point2.x()) {
        continue;
      }
      else if (point1.x() == point2.x() && point1.y() > point2.y()) {
        continue;
      }
      else {
        points[i] = point2;
        points[j] = point1;
      }
    }
  }

  return QPointF(points[1].x()+points[2].x(),points[1].y()+points[1].y())/2.0;
}
#endif
