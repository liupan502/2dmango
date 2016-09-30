#include "DesignData.h"

bool DesignData::FindStartPoint(QPointF currentPoint, QPointF& startPoint) {
  std::set<QPointF> points;
  for (std::map<std::string, CornerData*>::iterator it = corner_data_map_.begin(); it != corner_data_map_.end(); it++) {
    CornerData* corner = it->second;
    QPointF corner_position = corner->LikePosition();
    QVector2D vec1 = QVector2D(currentPoint - corner_position);
    if (vec1.length() > 50) {
      continue;
    }
    std::vector<QPointF> start_points = corner->GetAvailableStartPoints();
    points.insert(start_points.begin(), start_points.end());
  }

  if (points.size() > 0) {
    qreal distance = 100;
    for (std::set<QPointF>::iterator it = points.begin(); it != points.end(); it++) {
      QPointF tmp_point = *it;
      QVector2D vec2 = QVector2D(tmp_point - currentPoint);
      if (vec2.length() < distance) {
        startPoint = tmp_point;
        distance = vec2.length();
      }
    }
  }
  else {
    return false;
  }
  return true;
}