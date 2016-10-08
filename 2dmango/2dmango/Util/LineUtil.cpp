#include "LineUtil.h"
bool IsPointInLine(QPointF point, QLineF line) {
  if (line.isNull() || point.isNull()) {
    return false;
  }

  QVector2D vec1 = QVector2D(point - line.p1());
  if (vec1.isNull()) {
    return true;
  }
  vec1.normalize();

  QVector2D vec2 = QVector2D(line.p2() - point);
  if (vec2.isNull()) {
    return true;
  }
  vec2.normalize();

  if (EqualVector2D(vec1,vec2)) {
    return true;
  }
  else {
    return false;
  }
}

bool IsSameLine(QLineF line1, QLineF line2) {
if (line1.isNull() || line2.isNull()) {
return false;
}
QLineF unit_vector1 = line1.unitVector();
QVector2D vec1 = QVector2D (unit_vector1.p1()-unit_vector1.p2());
QLineF unit_vector2 = line2.unitVector();
QVector2D vec2 = QVector2D(unit_vector2.p1() - unit_vector2.p2());
if (!EqualVector2D(vec1,vec2) && !EqualVector2D(vec1,-vec2)) {
return false;
}

QVector2D vec3 = QVector2D(line1.p1() - line2.p1());
QVector2D vec4 = QVector2D(line1.p1() - line2.p2());
if (vec3.isNull() || vec4.isNull()) {
return true;
}
vec3.normalize();
vec4.normalize();
if (EqualVector2D(vec3, vec4) || EqualVector2D(vec3, -vec4)) {
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
  
  for (int j = i+1; j < points.size(); j++) {
    QPointF point1 = points[i];
    QPointF point2 = points[j];
    
    if (point1.x() > point2.x()) {
      continue;
    }
    else if (point1.x() == point2.x() && point1.y() > point2.y()) {
      continue;
    }
    else {
      QPointF tmp_point = points[i];
      points[i] = points[j];
      points[j] = tmp_point;
    }
  }
}

  return QPointF(points[1].x()+points[2].x(),points[1].y()+points[2].y())/2.0;
}

bool EqualVector2D(QVector2D vec1, QVector2D vec2) {

  vec1.normalize();
  vec2.normalize();
  QVector2D vec3 = vec1 - vec2;
  if (vec3.length() < 0.001) {
    return true;
  }
  else {
    return false;
  }

}

int PointDistanceToLine(QPointF point, QLineF line, qreal& distance) {
  int status = 0;
  QLineF normal_line = NormalLineWithPoint(line, point);
  QPointF tmp_point;
  normal_line.intersect(line,&tmp_point);
  if (IsPointInLine(tmp_point, line)) {
    status = 1;
  }
  distance = QVector2D(point - tmp_point).length();
  return status;
}

QLineF NormalLineWithPoint(QLineF line, QPointF point,qreal radius) {
  QLineF normal_line;
  QLineF tmp_normal_vector = line.normalVector();
  QVector2D tmp_vec = QVector2D(tmp_normal_vector.p2() - tmp_normal_vector.p1());
  tmp_vec.normalize();
  tmp_vec = tmp_vec*radius;
  normal_line = QLineF(point, point + tmp_vec.toPoint());
  return normal_line;
}