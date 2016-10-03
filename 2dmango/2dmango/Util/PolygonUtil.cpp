#include "PolygonUtil.h"


bool IsCounterclockwisePolygon(std::vector<QPointF> polygon) {
  int point_size = polygon.size();
  if (point_size < 3) {
    return false;
  }
  QPointF point = polygon[0];
  int index = 0;
  for (int i = 1; i < point_size; i++) {
    QPointF tmp_point = polygon[i];
    if (tmp_point.y() > point.y()) {
      point = tmp_point;
      index = i;
    }
  }

  int previous_index = (point_size+index-1)%point_size;
  QPointF previous_point = polygon[previous_index];
  int next_index = (index+1)%point_size;
  QPointF next_point = polygon[next_index];
  if (next_point.x() < previous_point.x()) {
    return true;
  }
  else {
    return false;
  }
}

void PolygonFlipY(std::vector<QPointF>& polygon) {
  std::vector<QPointF>::iterator it;
  for (it = polygon.begin(); it != polygon.end(); it++) {
    it->setY(-it->y());
  }
}

bool IsPointInPolygon(QPointF point, std::vector<QPointF> polygon) {
  int size = polygon.size();
  std::vector<QPointF> intersect_points;
  for (int i = 0; i < size; i++) {
    QPointF point1 = polygon[i];
	  QPointF point2 = polygon[(i + 1) % size];
	  QLineF line1(point1, point2);
	  QLineF line2(QPointF(point.x() - 9999.0f, point.y()),QPointF(point.x() + 9999.0f,point.y()));
	  QPointF intersect_point;
	if (line1.intersect(line2, &intersect_point) == QLineF::BoundedIntersection) {
      intersect_points.push_back(intersect_point);
	}
  }

  std::vector<QPointF> left_points, right_points;
  int intersect_points_size = intersect_points.size();
  for (int i = 0; i < intersect_points_size; i++) {
	if (intersect_points[i].x() < point.x()) {
	  left_points.push_back(intersect_points[i]);
	}
	else {
	  right_points.push_back(intersect_points[i]);
	}
  }

  if (left_points.size() % 2 == 0) {
	  return false;
  }
  else {
	  return true;
  }
}