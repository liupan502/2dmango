#include "RoomData.h"
#include "WallData.h"
#include "CornerData.h"
#include "Util/PolygonUtil.h"
#include "PointData.h"
#include <assert.h>
#include <QJsonArray>
#include <QPolygonF>
QJsonObject RoomData::ToJson() {
  QJsonObject object;
  QJsonObject parent_object = BaseData::ToJson();
  AttachJsonObject(object, parent_object);
  object.insert("func_name", QJsonValue(func_name_.c_str()));

  QJsonArray wall_name_array;
  for (int i = 0; i < walls_.size(); i++) {
    WallData* wall_data = walls_[i];
    QJsonValue wall_data_value(wall_data->name().c_str());
    wall_name_array.append(wall_data_value);
  }
  object.insert("wall_names", QJsonValue(wall_name_array));

  QJsonArray ceiling_name_array;
  for (int i = 0; i < ceiling_names_.size(); i++) {
    QJsonValue ceiling_name_value(QString::fromStdString(ceiling_names_[i]));
    ceiling_name_array.append(ceiling_name_value);
  }
  object.insert("ceiling_names", ceiling_name_array);
  return object;
}

void RoomData::InitWithObject(QJsonObject& jsonObject) {
  if (jsonObject.contains("func_name")) {
    func_name_ = jsonObject["func_name"].toString().toStdString();
  }
  else {
    func_name_ = "";
  }

  walls_.clear();
  QJsonArray wall_name_array;
  if (jsonObject.contains("wall_names")) {
    wall_name_array = jsonObject["wall_names"].toArray();
    for (int i = 0; i < wall_name_array.size(); i++) {
      std::string  wall_name_value = wall_name_array[i].toString().toStdString();
      WallData* wall_data = new WallData();
      wall_data->set_name(wall_name_value);
      walls_.push_back(wall_data);
    }
  }

  ceiling_names_.clear();
  if (jsonObject.contains("ceiling_names")) {
    QJsonArray ceiling_name_array = jsonObject["ceilings"].toArray();
    for (int i = 0; i < ceiling_name_array.size(); i++) {
      std::string ceiling_name = ceiling_name_array[i].toString().toStdString();
      ceiling_names_.push_back(ceiling_name);
    }
  }
}

void RoomData::UpdateWallDatas(std::map<std::string, WallData*>& wallDataMap) {
  for (int i = 0; i < walls_.size(); i++) {
    WallData* wall = walls_[i];
    std::string wall_name = wall->name();
    std::map<std::string, WallData*>::iterator it = wallDataMap.find(wall_name);
    if (it != wallDataMap.end()) {
      WallData* tmp_wall = it->second;
      if (wall != tmp_wall) {
        delete wall;
        walls_[i] = tmp_wall;
      }
    }
  }
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
    std::string connect_point_name = "";
    if (current_wall->IsStartCorner(previousCorner)) {
      if (next_wall->IsStartCorner(previousCorner)) {
        connect_point_name = current_wall->line().start_point_name() == next_wall->line().start_point_name() ?
          current_wall->line().start_point_name() : "";
      }
      else {
        connect_point_name = current_wall->line().start_point_name() == next_wall->line().end_point_name() ?
          current_wall->line().start_point_name() : "";
      }
    }
    else {
      if (next_wall->IsStartCorner(previousCorner)) {
        connect_point_name = current_wall->line().end_point_name() == next_wall->line().start_point_name() ?
          current_wall->line().end_point_name() : "";
      }
      else {
        connect_point_name = current_wall->line().end_point_name() == next_wall->line().end_point_name() ?
          current_wall->line().end_point_name() : "";
      }
    }
    //std::string connect_point_name = current_wall->line().find_connected_point(next_wall->line());
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
    if (wall->IsEndCorner(previous_corner)) {
      vector = -vector;
    }
    // end to start 
    if (is_counterclockwise) {
      vector = -vector;     
    } 
    if (wall->name() == "10") {
      int a = 0;
    }
    wall->set_normal_vector(vector);
    previous_corner = corner;
  }

}

std::vector<CornerData*> RoomData::GetCorners() {
  std::vector<CornerData*> corners;
  int size = walls_.size();
  if (size < 3) {
    return corners;
  }  
  CornerData* previous_corner = NULL;
  
  for (int i = 0; i < size; i++) {
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
    if (corner_set2.find(*it) == corner_set2.end()) {
      extra_corners.push_back(*it);
    }
  }
  std::vector<QPointF> polygon = get_points(corners2);
  std::vector<QPointF> extra_points = get_points(extra_corners);
  //for(int i=0;i<extra_corners.siz)
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
  for (std::vector<CornerData*>::iterator it = corners.begin(); it != corners.end(); it++) {
    CornerData* corner = *it;
    assert(corner->RelateWalls().size() > 0);
    WallData* wall = corner->RelateWalls()[0];
    if (wall->IsStartCorner(corner)) {
      points.push_back(corner->GetPoint(wall->line().start_point_name())->point());
    }
    else {
      points.push_back(corner->GetPoint(wall->line().end_point_name())->point());
    }
  }
  return points;
}

QVector2D RoomData::WallOutsideDirection(WallData* wallData) {
  QVector2D outside_direction;
  /*WallData* tmp_wall = NULL;
  int wall_index = -1;
  for (int i = 0; i < walls_.size(); i++) {
    if (wallData = walls_[i]) {
      tmp_wall = walls_[i];
      wall_index = i;
      break;
    }
  }
  if (tmp_wall == NULL) {
    return outside_direction;
  }

  std::vector<PointData*> room_polygon = polygon();
  int size = room_polygon.size();
  std::vector<QPointF> points;
  for (int i = 0; i < size; i++) {
    points.push_back(room_polygon[i]->point());
  }
  PolygonFlipY(points);
  bool is_counterclockwise = IsCounterclockwisePolygon(points);
  WallData* next_wall = walls_[(wall_index + 1) % walls_.size()];

  CornerData* corner = wallData->GetConnectedCorner(next_wall);*/

  return outside_direction;
}

std::vector<QPointF> RoomData::InnerWallPoints() {
  std::vector<QPointF> result;
  std::vector<PointData*> room_polygon = polygon();
  int size = room_polygon.size();
  std::vector<QPointF> points;
  for (int i = 0; i < size; i++) {
    points.push_back(room_polygon[i]->point());
  }
  PolygonFlipY(points);
  bool is_counterclockwise = IsCounterclockwisePolygon(points);

  for (int i = 0; i < walls_.size(); i++) {
    WallData* wall_data = walls_[i];
    QVector2D vec1 (wall_data->start_corner_position() - wall_data->end_corner_position());
    QVector2D vec2 = wall_data->normal_vector();
    float val = vec1.x()*vec2.y() - vec1.y()*vec2.x();
    val = val*(is_counterclockwise ? 1 : -1);
    LineData tmp_line = (val > 0) ? wall_data->line() : wall_data->generate_line();
    CornerData* tmp_corner = is_counterclockwise ? wall_data->end_corner() : wall_data->start_corner();
    std::string point_name = is_counterclockwise ? tmp_line.end_point_name() :tmp_line.start_point_name();
    QPointF point = tmp_corner->GetPoint(point_name)->point();
    result.push_back(point);
  }

  return result;
}

bool RoomData::IsPointIn(QPointF point) {
  std::vector<QPointF> inner_wall_points = InnerWallPoints();
  QPolygonF tmp_polygon;
  for (int i = 0; i < inner_wall_points.size(); i++) {
    tmp_polygon << inner_wall_points[i];
  }

  return tmp_polygon.containsPoint(point, Qt::OddEvenFill);
}

void RoomData::AddCeiling(const std::string& ceilingName) {
  ceiling_names_.push_back(ceilingName);
}

void RoomData::RemoveCeiling(const std::string& ceilingName) {
  std::vector<std::string>::iterator it = find(ceiling_names_.begin(), ceiling_names_.end(),ceilingName);
  if (it != ceiling_names_.end()) {
    ceiling_names_.erase(it);
  }
}

