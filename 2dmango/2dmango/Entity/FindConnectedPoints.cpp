#include "DesignData.h"
#include <assert.h>
#include "Util/PolygonUtil.h"
bool DesignData::FindConnectedPoints(QPointF currentPoint, std::string wallName, std::vector<QPointF>& outputPoints) {
  WallData* wall_data = wall_data_map_[wallName];
  QVector2D vec = wall_data->WallPerpendicularVector();
  outputPoints.clear();
  std::vector<CornerData*> corners;
  std::vector<WallData*> walls;
  std::vector<QPointF> points;
  std::vector<qreal> offsets;
  std::map<std::string, WallData*>::iterator it;

  for (it = wall_data_map_.begin(); it != wall_data_map_.end(); it++) {
    WallData* wall = it->second;
    QVector2D normal_vector = wall->WallPerpendicularVector();
    QLineF tmp_line(QLineF(currentPoint, QPointF(currentPoint.x() + normal_vector.x(), currentPoint.y() + normal_vector.y())));
    QPointF tmp_point;
    if (tmp_line.intersect(wall->WallLine(), &tmp_point) == QLineF::NoIntersection) {
      continue;
    }
    
    QVector2D tmp_vec = QVector2D(currentPoint - tmp_point);
    QPointF start_position = wall->start_corner_position();
    QVector2D start_vec = QVector2D(start_position - tmp_point);
    if (start_vec.length() < 20) {
      std::vector<WallData*> relate_walls = wall->start_corner()->RelateWalls();
      int drawing_wall_num = 0;
      for (int i = 0; i < relate_walls.size(); i++) {
        if (relate_walls[i]->status() == DRAWING_WALL_DATA) {
          drawing_wall_num++;
        }       
      }
      if (drawing_wall_num <= 1) {
        corners.push_back(wall->start_corner());
        walls.push_back(wall);
        points.push_back(QPointF(tmp_vec.x()+start_position.x(), tmp_vec.y() + start_position.y()));
        offsets.push_back(start_vec.length());
      }
      
    }

    QPointF end_position = wall->end_corner_position();
    QVector2D end_vec = QVector2D(end_position - tmp_point);
    if (end_vec.length() < 20) {
      std::vector<WallData*> relate_walls = wall->end_corner()->RelateWalls();
      int drawing_wall_num = 0;
      for (int i = 0; i < relate_walls.size(); i++) {
        if (relate_walls[i]->status() == DRAWING_WALL_DATA) {
          drawing_wall_num++;
        }
      }
      if (drawing_wall_num <= 1) {
        corners.push_back(wall->end_corner());
        walls.push_back(wall);
        points.push_back(QPointF(tmp_vec.x() + end_position.x(), tmp_vec.y() + end_position.y()));
        offsets.push_back(end_vec.length());
      }
    }
    
  }

  std::vector < WallData* >::iterator wall_it = walls.begin();
  std::vector<CornerData*>::iterator corner_it = corners.begin();
  std::vector<QPointF>::iterator point_it = points.begin();
  std::vector<qreal>::iterator offset_it = offsets.begin();
  for (; wall_it != walls.end();) {
    QVector2D tmp_vec = (*wall_it)->WallPerpendicularVector();
    tmp_vec.normalize();
    QPointF point = (*wall_it)->IsStartCorner(*corner_it) ? (*wall_it)->start_corner_position() :
      (*wall_it)->end_corner_position();
    QLineF line(point, (*point_it));
    bool bSave = true;
    for (std::map<std::string, WallData*>::iterator it = wall_data_map_.begin(); it != wall_data_map_.end(); it++) {
      QLineF tmp_line = it->second->WallLine();
      QPointF tmp_point;
      if (tmp_line.intersect(line, &tmp_point) == QLineF::BoundedIntersection && it->second != (*wall_it)) {
        bSave = false;
        break;
      }
    }

    if (bSave) {
      wall_it++;
      corner_it++;
      point_it++;
      offset_it++;
    }
    else {
      wall_it = walls.erase(wall_it);
      corner_it = corners.erase(corner_it);
      point_it = points.erase(point_it);
      offset_it = offsets.erase(offset_it);
    }
  }

  if (walls.size() == 0) {
    return false;
  }

  int min_offset = offsets[0];
  int index = 0;
  for (int i = 0; i < offsets.size(); i++) {
    if (offsets[i] < min_offset) {
      min_offset = offsets[i];
      index = i;
    }
  }

  QPointF point = compute_connected_point(wall_data, corners[index], currentPoint);  
  outputPoints.push_back(point);
  return true;
}

QPointF DesignData::compute_connected_point(WallData* wall, CornerData* corner,QPointF currentPoint) {
  QPointF point;
  CornerData* first_corner = NULL;
  if (wall->start_corner()->RelateWalls().size() == 1) {
    first_corner = wall->start_corner();
  }
  else if (wall->end_corner()->RelateWalls().size() == 1) {
    first_corner = wall->end_corner();
  }
  if (first_corner == NULL || corner == NULL) {
    return point;
  }

  std::vector<CornerData*> path = first_corner->FindPathTo(corner);
  std::vector<QPointF> polygon;
  for (int i = 0; i < path.size(); i++) {
    QPointF point = path[i]->LikePosition();
    assert(!point.isNull());
    polygon.push_back(point);
  }
  PolygonFlipY(polygon);
  bool is_counterclockwise = IsCounterclockwisePolygon(polygon);
  int size = path.size();
  CornerData* corner1 = path[size - 1];
  CornerData* corner2 = path[size - 2];
  WallData* wall = NULL;
  for (std::map<std::string, WallData*>::iterator it = wall_data_map_.begin(); it != wall_data_map_.end(); it++) {
    WallData* tmp_wall = it->second;
    if (wall->DoContainCorner(corner1) && wall->DoContainCorner(corner2)) {
      wall = tmp_wall;
      break;
    }
  }
  
  if (wall->status() == DRAWING_WALL_DATA) {
    point = wall->IsStartCorner(corner) ? wall->start_corner_position() : wall->end_corner_position();
  }
  else {
    QVector2D vec = wall->WallPerpendicularVector();
    vec.normalize();
    QLineF line1 = QLineF(currentPoint,currentPoint+ vec.toPointF());
    QLineF line2 = wall->WallLine();
    QPointF point1;
    line1.intersect(line2, &point1);
    QVector2D vec2 = QVector2D(currentPoint - point1);
    qreal length = vec2.length();
    QPointF point3  = wall->IsStartCorner(corner) ? wall->start_corner_position() : wall->end_corner_position();
    QPointF point4 = point3 + vec2.toPointF();
    QLineF line3(point4, point3);
    QPointF point5, point6;
    line3.intersect(wall->line().Line(), &point5);
    line3.intersect(wall->generate_line().Line(), &point6);
    QVector2D vec3(point5 - point4);
    QVector2D vec4(point6 - point4);
    point = vec3.length() < vec4.length() ? point5 : point6;
  }
  return point;
}