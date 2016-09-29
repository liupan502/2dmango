#include "DesignData.h"

bool DesignData::FindConnectedPoints(QPointF currentPoint, std::string wallName, std::vector<QPointF>& points) {
  WallData* wall_data = wall_data_map_[wallName];
  QVector2D vec = wall_data->WallPerpendicularVector();
  points.clear();
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






  

  return false;
}

QPointF DesignData::compute_connected_point(WallData* wall, CornerData* corner) {
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
  return point;
}