#include "RoomData.h"
#include "WallData.h"
#include "CornerData.h"
#include "Util/PolygonUtil.h"
#include "PointData.h"
#include <assert.h>
std::string RoomData::ToJson() {
  return " ";
}

RoomData::RoomData():BaseData(){
  
}

RoomData::RoomData(std::string name, std::vector<WallData*> walls) : BaseData(name) {
  walls_ = walls;
  for (int i = 0; i < walls_.size(); i++) {
    walls_[i]->set_status(ROOM_WALL_DATA);
  }
}

bool RoomData::CanComputeWallGeometry(std::set<WallData*>excludeWalls) {
  bool result = true;
  CornerData* previous_corner = NULL;
  int walls_size = walls_.size();
  for (int i = 0; i < walls_size; i++) {
    WallData* wall = walls_[i];
    if (excludeWalls.find(wall) != excludeWalls.end()) {
      continue;
    }

    if (previous_corner == NULL) {
      previous_corner = find_previous_corner(i);
      continue;
    }
    if (!check_wall(previous_corner, i, excludeWalls)) {
      result = false;
      break;
    }
  }
  return result;
}



CornerData* RoomData::find_previous_corner(int currentIndex) {
  int size = walls_.size();
  int previous_index = (size+currentIndex-1)%size;
  WallData* current_wall = walls_[currentIndex];
  WallData* previous_wall = walls_[previous_index];
  CornerData* previous_corner = current_wall->GetConnectedCorner(previous_wall);
  return previous_corner;
}

bool RoomData::check_wall(CornerData* previousCorner, int currentIndex, std::set<WallData*> excludeWalls) {
  bool result = false;
  int wall_size = walls_.size();
  int next_index = (currentIndex+1)%wall_size;
  WallData* current_wall = walls_[currentIndex];
  WallData* next_wall = walls_[next_index];
  previousCorner = current_wall->GetConnectedCorner(next_wall);
  if (excludeWalls.find(next_wall) != excludeWalls.end()) {
    result = true;
  }
  else {
    std::string connect_point_name = current_wall->line().find_connected_point(next_wall->line());
    if (connect_point_name != "") {
      result = true;
    }
  } 
  return result;
}

std::vector<WallData*> RoomData::walls() {
  return walls_;
}

std::vector<PointData*> RoomData::polygon() {
  std::vector<PointData*> polygon;
  int wall_size = walls_.size();
  for (int i = 0; i < wall_size; i++) {
    WallData* wall = walls_[i];
    WallData* next_wall = walls_[(i+1)%wall_size];
    PointData* point = wall->GetConnectedPoint(next_wall);
    polygon.push_back(point);
  }
  return polygon;
}

void RoomData::GenerateLines() {
  std::vector<PointData*> room_polygon = polygon();
  int size = room_polygon.size();
  std::vector<QPointF> points;
  for (int i = 0; i < size; i++) {
    points.push_back(room_polygon[i]->point());
  }
  PolygonFlipY(points);
  bool is_counterclockwise = IsCounterclockwisePolygon(points);
  CornerData* previous_corner = walls_[0]->start_corner();
  for (int i = 0; i < size; i++) {
    WallData* wall = walls_[i];
    WallData* next_wall = walls_[(i+1)%size];
    CornerData* corner = wall->GetConnectedCorner(next_wall);
    if (!wall->normal_vector().isNull()) {
      previous_corner = corner;
      continue;
    }

    QLineF vector_line = wall->line().Line().normalVector();
    QVector2D vector = QVector2D(vector_line.p2() - vector_line.p1());
    // end to start 
    if (is_counterclockwise) {
      vector = -vector;     
    }    
    wall->set_normal_vector(vector);
  }

}

std::vector<CornerData*> RoomData::GetCorners() {
  std::vector<CornerData*> corners;
  int size = walls_.size();
  if (size < 3) {
    return corners;
  }  
  CornerData* previous_corner = NULL;
  
  for (int i = 1; i < size; i++) {
    if (walls_[i]->IsEndCorner(previous_corner)) {
      previous_corner = walls_[i]->start_corner();      
    }
    else {
      previous_corner = walls_[i]->end_corner();
    }
    corners.push_back(previous_corner);
  }
  return corners;
}

bool RoomData::IsIncludedIn(RoomData otherRoom) {
  bool result = true;
  std::vector<CornerData*> corners1 = GetCorners();
  std::vector<CornerData*> corners2 = otherRoom.GetCorners();
  std::set<CornerData*> corner_set1, corner_set2;
  corner_set1.insert(corners1.begin(), corners1.end());
  corner_set2.insert(corners2.begin(), corners2.end());
  std::vector<CornerData*> extra_corners;
  for (std::set<CornerData*>::iterator it = corner_set1.begin(); it != corner_set1.end(); it++) {
    if (corner_set2.find(*it) != corner_set2.end()) {
      extra_corners.push_back(*it);
    }
  }
  std::vector<QPointF> polygon = get_points(corners2);
  std::vector<QPointF> extra_points = get_points(extra_corners);
  for (std::vector<QPointF>::iterator it = extra_points.begin(); it != extra_points.end(); it++) {
    if (!IsPointInPolygon(*it, polygon)) {
      result = false;
      break;
    }
  }
  return result;
}

std::vector<QPointF> RoomData::get_points(std::vector<CornerData*> corners) {
  std::vector<QPointF> points;
  for (std::set<CornerData*>::iterator it = corners.begin(); it != corners.end(); it++) {
    CornerData* corner = *it;
    assert(corner->RelateWalls().size() > 0);
    WallData* wall = corner->RelateWalls()[0];
    if (wall->IsStartCorner(corner)) {
      points.push_back(corner->GetPoint(wall->start_corner_name())->point());
    }
    else {
      points.push_back(corner->GetPoint(wall->end_corner_name())->point());
    }
  }
  return points;
}