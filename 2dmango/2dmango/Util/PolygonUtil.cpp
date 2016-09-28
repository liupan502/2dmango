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