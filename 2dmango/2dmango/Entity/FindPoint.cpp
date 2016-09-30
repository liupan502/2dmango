#include "DesignData.h"
#include <assert.h>

bool DesignData::FindStartPoint(QPointF currentPoint, QPointF& startPoint) {
  std::vector<QPointF> points;
  for (std::map<std::string, CornerData*>::iterator it = corner_data_map_.begin(); it != corner_data_map_.end(); it++) {
    CornerData* corner = it->second;
    QPointF corner_position = corner->LikePosition();
    QVector2D vec1 = QVector2D(currentPoint - corner_position);
    if (vec1.length() > 50) {
      continue;
    }
    std::vector<QPointF> start_points = corner->GetAvailableStartPoints();    
    for (int i = 0; i < start_points.size(); i++) {
      points.push_back(start_points[i]);
    }
  }

  if (points.size() > 0) {
    qreal distance = 100;
    for (std::vector<QPointF>::iterator it = points.begin(); it != points.end(); it++) {
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

bool DesignData::FindEndPoint(WallData* wall_data, CornerData* corner, QPointF currentPoint, QPointF& endPoint) {

  assert(wall_data != NULL && corner != NULL);
  endPoint = QPointF();
  QVector2D vec = wall_data->WallVector();
  vec.normalize();
  
  QLineF line1(currentPoint + vec.toPoint() * 1000, currentPoint - vec.toPoint() * 1000);
  std::vector<WallData*> related_walls = corner->RelateWalls();
  for (int i = 0; i < related_walls.size(); i++) {
    WallData* related_wall = related_walls[i];
    if (related_wall->status() == DRAWING_WALL_DATA ) {
      if (related_wall->IsStartCorner(corner)) {
        endPoint = related_wall->start_corner_position();
      }
      else {
        endPoint = related_wall->end_corner_position();
      }
      break;
    }

    QLineF line2 = related_wall->line().Line();
    QPointF point2;
    if (line2.intersect(line1, &point2) != QLineF::BoundedIntersection) {
      continue;
    }
    QLineF line3 = related_wall->generate_line().Line();
    QPointF point3;
    if (line3.intersect(line1, &point3) != QLineF::BoundedIntersection) {
      continue;
    }

    QVector2D vec2(point2 - currentPoint);
    QVector2D vec3(point3 - currentPoint);

    if (vec2.length() > vec3.length()) {
      endPoint = point3;
    }
    else {
      endPoint = point2;
    }
  }
  if (endPoint.isNull()) {
    return false;
  }
  else {
    return true;
  }  
}