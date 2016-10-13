#include "DesignData.h"

#include <math.h>
#include <set>
#include "WallPath.h"
#include <assert.h>
#include <QJsonArray>
QJsonObject DesignData::ToJson(){
  QJsonObject object;
  QJsonObject parent_object = BaseData::ToJson();
  AttachJsonObject(object, parent_object);
  QJsonArray wall_data_array;
  for (std::map<std::string, WallData*>::iterator it = wall_data_map_.begin(); it != wall_data_map_.end(); it++) {
    WallData* wall_data = it->second;
    QJsonObject wall_data_object = wall_data->ToJson();
    wall_data_array.append(wall_data_object);
  }
  object.insert("walls",QJsonValue(wall_data_array));

  QJsonArray corner_data_array;
  for (std::map<std::string, CornerData*>::iterator it = corner_data_map_.begin(); it != corner_data_map_.end(); it++) {
    CornerData* corner_data = it->second;
    QJsonObject corner_data_object = corner_data->ToJson();
    corner_data_array.append(corner_data_object);
  }
  object.insert("corners",QJsonValue(corner_data_array));

  QJsonArray opening_data_array;
  for (std::map<std::string, OpeningData*>::iterator it = opening_data_map_.begin(); it != opening_data_map_.end(); it++) {
    OpeningData* opening_data = it->second;
    QJsonObject opening_data_value = opening_data->ToJson();
    opening_data_array.append(opening_data_value);
  }
  object.insert("openings", QJsonValue(opening_data_array));

  QJsonArray room_data_array;
  for (std::map<std::string, RoomData*>::iterator it = room_data_map_.begin(); it != room_data_map_.end(); it++) {
    RoomData* room_data = it->second;
    QJsonObject room_data_value = room_data->ToJson();
    room_data_array.append(room_data_value);
  }
  object.insert("rooms", QJsonValue(room_data_array));


  return QJsonObject();
}

void DesignData::InitWithObject(QJsonObject& jsonObject) {
  BaseData::InitWithObject(jsonObject);

  if (jsonObject.contains("walls")) {
    QJsonArray wall_data_array = jsonObject["walls"].toArray();
    for (int i = 0; i < wall_data_array.size(); i++) {
      QJsonObject wall_object = wall_data_array[i].toObject();
      WallData* wall_data = new WallData();
      wall_data->InitWithObject(wall_object);
      wall_data_map_.insert(make_pair(wall_data->name(), wall_data));
    }
  }

  if (jsonObject.contains("corners")) {
    QJsonArray corner_data_array = jsonObject["corners"].toArray();
    for (int i = 0; i < corner_data_array.size(); i++) {
      QJsonObject corner_object = corner_data_array[i].toObject();
      CornerData* corner_data = new CornerData();
      corner_data->InitWithObject(corner_object);
      corner_data_map_.insert(make_pair(corner_data->name(), corner_data));
    }
  }

  if (jsonObject.contains("openings")) {
    QJsonArray opening_data_array = jsonObject["openings"].toArray();
    for (int i = 0; i < opening_data_array.size(); i++) {
      QJsonObject opening_object = opening_data_array[i].toObject();
      OpeningData* opening_data = new OpeningData();
      opening_data->InitWithObject(opening_object);
      opening_data_map_.insert(make_pair(opening_data->name(), opening_data));
    }

    if (jsonObject.contains("rooms")) {
      QJsonArray room_data_array = jsonObject["rooms"].toArray();
      for (int i = 0; i < room_data_array.size(); i++) {
        QJsonObject room_object = room_data_array[i].toObject();
        RoomData* room_data = new RoomData();
        room_data->InitWithObject(room_object);
        room_data_map_.insert(make_pair(room_data->name(), room_data));
      }
    }
  }
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
  std::map<std::string, CornerData*>::iterator corner_it;
  for (corner_it = corner_data_map_.begin(); corner_it != corner_data_map_.end(); corner_it++) {
    CornerData* corner = corner_it->second;
    corner->UpdateRelatedInfo();
  }

  std::map<std::string,WallPath*> wall_paths = WallPathFactory::CreateWallPaths(wall_data_map_);
  std::set<WallData*> exclude_walls;
  find_unclosed_walls(exclude_walls);
  std::set<WallPath*> exclude_wall_paths;
  
  for (std::set<WallData*>::iterator it = exclude_walls.begin(); it != exclude_walls.end(); it++) {
    WallData* exclude_wall = *it;
    for (std::map<std::string, WallPath*>::iterator path_it = wall_paths.begin(); path_it != wall_paths.end(); path_it++) {
      if (path_it->second->DoContianWall(exclude_wall)) {
        exclude_wall_paths.insert(path_it->second);
        wall_paths.erase(path_it);
        break;
      }
    }
    
  }
  
  
  while (true) {
    if (wall_paths.size() == 0) {
      break;
    }
    int previous_num = wall_paths.size(); 
    WallPath* wall_path = NULL;
    WallData* start_wall = find_start_wall(exclude_walls);
    for (std::map<std::string, WallPath*>::iterator wall_path_map_it = wall_paths.begin();
      wall_path_map_it != wall_paths.end(); wall_path_map_it++) {
      if (wall_path_map_it->second->DoContianWall(start_wall)) {
        wall_path = wall_path_map_it->second;
        continue;
      }
    }

    WallPath room = wall_path->GetRoom(exclude_wall_paths);
    std::vector<WallData*> tmp_wall_datas = room.walls();
    std::set<WallPath*> used_paths;      
    for (std::map<std::string, WallPath*>::iterator tmp_it = wall_paths.begin(); tmp_it != wall_paths.end(); tmp_it++) {        
      for (int i = 0; i < tmp_wall_datas.size(); i++) {
        if (tmp_it->second->DoContianWall(tmp_wall_datas[i])) {
          used_paths.insert(tmp_it->second);
          break;
        }
      }
    }   

    for (std::set<WallPath*>::iterator tmp_it = used_paths.begin(); tmp_it != used_paths.end(); tmp_it++) {
      WallPath* tmp_path = *tmp_it;
      if (tmp_path->IsUnshare(exclude_wall_paths) || tmp_path == wall_path) {
        //exclude_wall_paths.insert(tmp_path);
        std::map<std::string, WallPath*>::iterator tmp_wall_path_it = wall_paths.find(tmp_path->name());
        if (tmp_wall_path_it != wall_paths.end()) {
          wall_paths.erase(tmp_wall_path_it);
        }
      }
    }

    std::vector<WallPath*> tmp_exclude_wall_paths;
    for (std::set<WallPath*>::iterator tmp_it = used_paths.begin(); tmp_it != used_paths.end(); tmp_it++) {
      WallPath* tmp_path = *tmp_it;
      if (tmp_path->IsUnshare(exclude_wall_paths) || tmp_path == wall_path) {
        tmp_exclude_wall_paths.push_back(*tmp_it);
        std::vector<WallData*> tmp_wall_datas = tmp_path->walls();
        exclude_walls.insert(tmp_wall_datas.begin(), tmp_wall_datas.end());
      }
    }
    exclude_wall_paths.insert(tmp_exclude_wall_paths.begin(), tmp_exclude_wall_paths.end());

    if (wall_paths.size() == previous_num) {
      assert(false);
    }

    std::string room_name = generate_room_name();
    RoomData* room_data = new RoomData(room_name, tmp_wall_datas);
    room_data_map_.insert(make_pair(room_name, room_data));
     
   
  }

  for(std::set<WallPath*>::iterator it = exclude_wall_paths.begin(); it != exclude_wall_paths.end(); it++) {
    delete (*it);    
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

bool DesignData::IsEmpty() {
  if (corner_data_map_.size() > 0) {
    return false;
  }

  if (room_data_map_.size() > 0) {
    return false;
  }

  if (wall_data_map_.size() > 0) {
    return false;
  }

  return true;
}

CornerData* DesignData::FindCornerWithPosition(QPointF currentPosition) {
  CornerData* corner = NULL;
  for (std::map<std::string, CornerData*>::iterator it = corner_data_map_.begin();
    it != corner_data_map_.end(); it++) {
    QPointF corner_position = it->second->LikePosition();
    if (QVector2D(currentPosition - corner_position).length() < 20) {
      corner = it->second;
      break;
    }
  }
  return corner;
}

WallData* DesignData::find_start_wall(std::set<WallData*> excludeWalls) {
  WallData* start_wall = NULL;
  std::vector<WallData*> start_walls;
  std::map<std::string, WallData*>::iterator wall_map_it = wall_data_map_.begin();
  for (wall_map_it = wall_data_map_.begin(); wall_map_it != wall_data_map_.end(); wall_map_it++) {
    WallData* tmp_wall = wall_map_it->second;
    if (excludeWalls.find(tmp_wall) != excludeWalls.end()) {
      continue;
    }

    if (!tmp_wall->IsUnsharedWall(excludeWalls)) {
      continue;
    }

    QVector2D vec = tmp_wall->WallVector();
    if (abs(vec.x()) > abs(vec.y())) {
      continue;
    }

    if (start_wall == NULL) {
      start_wall = tmp_wall;
      continue;
    }   

    if ((tmp_wall->start_corner_position().x() < start_wall->start_corner_position().x()) &&
      tmp_wall->start_corner_position().x() < start_wall->end_corner_position().x()) {
      start_wall = tmp_wall;
      start_walls.clear();
      continue;
    }
   /* else if((tmp_wall->start_corner_position().x() == start_wall->start_corner_position().x()) ||
      tmp_wall->start_corner_position().x() ==  start_wall->end_corner_position().x()){
      start_walls.push_back(tmp_wall);
      continue;
    }*/

    if ((tmp_wall->end_corner_position().x() < start_wall->start_corner_position().x()) &&
      tmp_wall->end_corner_position().x() < start_wall->end_corner_position().x()) {
      start_wall = tmp_wall;
      start_walls.clear();
      continue;
    }
   /* else if ((tmp_wall->end_corner_position().x() == start_wall->start_corner_position().x()) ||
      tmp_wall->end_corner_position().x() == start_wall->end_corner_position().x()) {
      start_walls.push_back(tmp_wall);
    }*/
  }

  /*for (int i = 0; i < start_walls.size(); i++) {
    WallData* tmp_wall = start_walls[i];
    if ((tmp_wall->end_corner_position().y() > start_wall->start_corner_position().y()) ||
      tmp_wall->end_corner_position().y() > start_wall->end_corner_position().y()) {
      start_wall = tmp_wall;
      continue;
    }

    if ((tmp_wall->start_corner_position().y() > start_wall->start_corner_position().y()) ||
      tmp_wall->start_corner_position().y() > start_wall->end_corner_position().y()) {
      start_wall = tmp_wall;
      continue;
    }
  }*/
  return start_wall;
}

void DesignData::AddOpening(OpeningData* openingData) {
  std::map<std::string, OpeningData*>::iterator it = opening_data_map_.find(openingData->name());
  assert(it == opening_data_map_.end());
  opening_data_map_.insert(make_pair(openingData->name(),openingData));
}

std::string DesignData::GenerateOpeningName() {
  std::vector<std::string> names;
  std::map<std::string, OpeningData*>::iterator it;
  for (it = opening_data_map_.begin(); it != opening_data_map_.end(); it++) {
    names.push_back(it->first);
  }
  std::string name = generate_name(names);
  return name;
}

DesignData::~DesignData() {

  for (std::map<std::string, WallData*>::iterator it = wall_data_map_.begin(); it != wall_data_map_.end(); it++) {
    delete it->second;
    it->second = NULL;
  }

  for (std::map<std::string, CornerData*>::iterator it = corner_data_map_.begin(); it != corner_data_map_.end(); it++) {
    delete it->second;
    it->second = NULL;
  }

  for (std::map<std::string, RoomData*>::iterator it = room_data_map_.begin(); it != room_data_map_.end(); it++) {
    delete it->second;
    it->second = NULL;
  }

  for (std::map<std::string, OpeningData*>::iterator it = opening_data_map_.begin(); it != opening_data_map_.end(); it++) {
    delete it->second;
    it->second = NULL;
  }

}


