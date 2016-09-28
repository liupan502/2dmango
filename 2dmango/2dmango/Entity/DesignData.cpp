#include "DesignData.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <set>

std::string DesignData::ToJson(){
  return " ";
}

WallData* DesignData::AddWall(){
  std::string new_wall_name = generte_wall_name();
  WallData* new_wall = new WallData() ;
  new_wall->set_name(new_wall_name);
  wall_data_map_.insert(make_pair(new_wall_name,new_wall));
  return new_wall;
}

CornerData* DesignData::AddCorner(){
  std::string corner_name = generate_corner_name();
  CornerData* new_corner_data = new CornerData();
  new_corner_data->set_name(corner_name);
  corner_data_map_.insert(make_pair(corner_name,new_corner_data));
  return new_corner_data;
}

RoomData* DesignData::AddRoom(){
  RoomData* new_room_data = new RoomData();
  std::string new_room_name = generate_room_name();
  new_room_data->set_name(new_room_name);
  room_data_map_.insert(make_pair(new_room_name,new_room_data));
  return new_room_data;
}

std::string DesignData::generate_corner_name(){
  std::vector<std::string> names ;
  std::map<std::string,CornerData*>::iterator it;
  for(it = corner_data_map_.begin(); it != corner_data_map_.end();it++){
    names.push_back(it->first);
  }
  std::string name = generate_name(names);
  return name;
}

std::string DesignData::generate_room_name(){
  std::vector<std::string> names;
  std::map<std::string, RoomData*>::iterator it;
  for (it = room_data_map_.begin(); it != room_data_map_.end(); it++) {
    names.push_back(it->first);
  }
  std::string name = generate_name(names);
  return name;
}

std::string DesignData::generte_wall_name(){
  std::vector<std::string> names;
  std::map<std::string, WallData*>::iterator it;
  for (it = wall_data_map_.begin(); it != wall_data_map_.end(); it++) {
    names.push_back(it->first);
  }
  std::string name = generate_name(names);
  return name;
}

std::string DesignData::generate_line_name() {
  std::vector<std::string>used_names;
  std::map<std::string ,WallData*>::iterator it;
  for (it = wall_data_map_.begin(); it != wall_data_map_.end(); it++) {
    WallData* wall_data = it->second;
    std::vector<std::string> wall_used_names = wall_data->AllLineNames();
    used_names.insert(used_names.end(), wall_used_names.begin(), wall_used_names.end());
  }
  std::string name = generate_name(used_names);
  return name;
}

std::string DesignData::generate_point_name() {
  std::vector<std::string>used_names;
  std::map<std::string, CornerData*>::iterator it;
  for (it = corner_data_map_.begin(); it != corner_data_map_.end(); it++) {
    CornerData* corner_data = it->second;
    std::vector<std::string> corner_used_names = corner_data->AllPointNames();
    used_names.insert(used_names.end(), corner_used_names.begin(), corner_used_names.end());
  }
  std::string name = generate_name(used_names);
  return name;
}

std::string DesignData::generate_name(std::vector<std::string> used_names){
  int max_num = 0;
  for(int i=0;i<used_names.size();i++){
    int num = atoi(used_names[i].c_str());
    max_num = max_num > num? max_num : num;
  }
  char buf[32];
  memset(buf,0,sizeof(buf));
  sprintf(buf,"%d",max_num+1);
  return std::string(buf);
}

bool DesignData::FindConnectedPoints(QPointF currentPoint, std::string wallName, std::vector<QPointF>& points) {
  WallData* wall_data = wall_data_map_[wallName];
  QVector2D vec = wall_data->WallPerpendicularVector();
  points.clear();
  std::set<std::string> corners_set;
  std::map<std::string,WallData*>::iterator it;
  for (it = wall_data_map_.begin(); it != wall_data_map_.end(); it++) {
    WallData* wall_data = it->second;
    if (wall_data->status() == ROOM_WALL_DATA) {
      continue;
    }   
    CornerData* start_corner = wall_data->start_corner();
    if (start_corner != NULL) {
      QPointF start_corner_pos = wall_data->start_corner_position();
      std::string start_corner_name = start_corner->name();
      if (is_connected_point(currentPoint, vec, start_corner_pos)&&
          is_valid_connected_point(start_corner_name,wallName, corners_set)) {
        points.push_back(start_corner_pos);
        corners_set.insert(start_corner_name);
      }
    }
    else {

    }
    std::string end_corner_name = wall_data->end_corner_name();
    CornerData* end_corner = corner_data_map_[end_corner_name];
    if (end_corner) {
      QPointF end_corner_pos = wall_data->end_corner_position();
      if (is_connected_point(currentPoint, vec, end_corner_pos)&&
        is_valid_connected_point(end_corner_name, wallName, corners_set)) {
        points.push_back(end_corner_pos);
        corners_set.insert(end_corner_name);
      }
    }
    else {

    }
  }
  return (points.size() != 0);
}

bool DesignData::is_connected_point(QPointF currentPoint, QVector2D vec, QPointF testPoint) {
  QVector2D tmp_vec(testPoint-currentPoint);
  if (tmp_vec.length() < 1|| vec.length() < 1) {
    return false;
  }
  tmp_vec.normalize();
  vec.normalize();
  float abs_dot_product_value = abs(QVector2D::dotProduct(tmp_vec,vec));
  if (abs_dot_product_value > cos(5.0f/180.0f*M_PI) && abs_dot_product_value <= 1.0) {
    return true;
  }
  return false;
}

bool DesignData::is_valid_connected_point(std::string pointName, std::string wallName,std::set<std::string>cornersSet) {
  if (cornersSet.find(pointName) != cornersSet.end()) {
    return false;
  } 
  WallData* wall_data = wall_data_map_[wallName];
  std::string start_corner_name = wall_data->start_corner_name();
  std::vector<WallData*> walls = find_wall_with_corner_name(start_corner_name);
  for (int i = 0; i < walls.size(); i++) {
    WallData* wall = walls[i];
    if (wall->start_corner_name() == pointName || wall->end_corner_name() == pointName) {
      return false;
    }
  }
  return true;
}

std::vector<WallData*> DesignData::find_wall_with_corner_name(std::string cornerName) {
  std::vector<WallData*> walls;
  std::map<std::string,WallData*>::iterator it;
  for (it = wall_data_map_.begin(); it != wall_data_map_.end(); it++) {
    WallData* tmp_wall = it->second;
    if (tmp_wall->start_corner_name() == cornerName) {
      walls.push_back(tmp_wall);
    }
    else if (tmp_wall->end_corner_name() == cornerName) {
      walls.push_back(tmp_wall);
    }
  }
  return walls;
}

bool DesignData::FindAttachedCorner(QPointF currentPoint, std::string wallName, std::vector<CornerData*>& corners) {
  corners.clear();
  WallData* wall = wall_data_map_[wallName];  
  std::set<std::string> corners_set;
  std::map<std::string,WallData*>::iterator it;
  for (it = wall_data_map_.begin(); it != wall_data_map_.end(); it++) {
    WallData* tmp_wall = it->second;
    std::string tmp_start_corner_name = tmp_wall->start_corner_name();
    if (is_attached_corner(currentPoint, wallName, tmp_start_corner_name,corners_set) ){
      corners.push_back(tmp_wall->start_corner());
      corners_set.insert(tmp_start_corner_name);
    }
    std::string tmp_end_corner_name = tmp_wall->end_corner_name();
    if(is_attached_corner(currentPoint, wallName, tmp_end_corner_name, corners_set)) {
      corners.push_back(tmp_wall->end_corner());
      corners_set.insert(tmp_end_corner_name);
    }
    
  }
  if (corners.size() == 0) {
    return false;
  }
  return true;
}

bool DesignData::is_attached_corner(QPointF currentPoint, std::string wallName, std::string cornerName,std::set<std::string> cornersName) {
 
  if (cornersName.find(cornerName) != cornersName.end()) {
    return false;
  }
  WallData* wall = wall_data_map_[wallName];
  std::string start_corner_name = wall->start_corner_name();
  std::string end_corner_name = wall->end_corner_name();
  if (cornerName == start_corner_name) {
    return false;
  }

  if (cornerName == end_corner_name) {
    return false;
  }

  std::vector<WallData*> walls = find_wall_with_corner_name(cornerName);
  if (walls.size() == 0) {
    return false;
  }

  WallData* tmp_wall = walls[0];
  QPointF corner_position ;
  if (tmp_wall->start_corner_name() == cornerName) {
    corner_position = tmp_wall->start_corner_position();
  }
  else {
    corner_position = tmp_wall->end_corner_position();
  }
  QVector2D vec(corner_position-currentPoint);
  if (vec.length() > 50) {
    return false;
  }
  else {
    return true;
  }
}

QPointF DesignData::CornerPosition(std::string cornerName) {  
  std::map<std::string,WallData*>::iterator it;
  for (it = wall_data_map_.begin(); it != wall_data_map_.end(); it++) {
    WallData* wall = it->second;
    if (wall->start_corner_name() == cornerName) {
      return wall->start_corner_position();
    }
    if (wall->end_corner_name() == cornerName) {
      return wall->end_corner_position();
    }
  }
  return QPointF();
}

void DesignData::UpdateRoomInfo() {
  clear_rooms();
  std::set<WallData*> exclude_walls;
  find_unclosed_walls(exclude_walls);
  std::map<std::string,WallData*>::iterator it;
  for (it = wall_data_map_.begin(); it != wall_data_map_.end(); it++) {
    WallData* wall = it->second;
    if (exclude_walls.find(wall) != exclude_walls.end()) {
      continue;
    }
    if (!wall->IsUnsharedWall(exclude_walls)) {
      continue;
    }
    std::vector<WallData*> wall_path = wall->GetRoom(exclude_walls);
    if (wall_path.size() > 0) {
      update_exclude_walls(exclude_walls,wall_path);
      std::string room_name = generate_room_name();
      RoomData* room = new RoomData(room_name,wall_path);
      room_data_map_.insert(make_pair(room_name,room));
    }
  }
}

void DesignData::find_unclosed_walls(std::set<WallData*>& unclosedWalls) { 
  unclosedWalls.clear();
  std::map<std::string,CornerData*>::iterator it;
  for (it = corner_data_map_.begin(); it != corner_data_map_.end(); it++) {
    it->second->GetUnclosedWalls(unclosedWalls);
  }  
}

void DesignData::update_exclude_walls(std::set<WallData*>& exclude_walls, std::vector<WallData*>walls){
  std::set<WallData*> new_exclude_walls;
  for (int i = 0; i < walls.size(); i++) {
    if (walls[i]->IsUnsharedWall(exclude_walls)) {
      new_exclude_walls.insert(walls[i]);
    }
  }
  exclude_walls.insert(new_exclude_walls.begin(),new_exclude_walls.end());
}

void DesignData::clear_rooms() {
  std::map<std::string, RoomData*>::iterator it;
  for (it = room_data_map_.begin(); it != room_data_map_.end(); it++) {
    if (it->second != NULL) {
      delete it->second;
      it->second = NULL;
    }
  }
  room_data_map_.clear();
}
