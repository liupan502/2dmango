#include "CornerData.h"
#include "WallData.h"
#include <set>
#include <assert.h>

CornerData::CornerData(): has_position_data_(false){

}

std::string CornerData::ToJson() {
  return " ";
}

bool CornerData::has_position_data(){
  return has_position_data_;
}

void CornerData::set_position(QVector3D position){
  BaseGeometryData::set_position(position);
  has_position_data_ = true; 
}

CornerData::~CornerData() {
  std::map<std::string,PointData*>::iterator it;
  for (it = point_data_map_.begin(); it != point_data_map_.end(); it++) {
    PointData* point_data = it->second;
    if (point_data != NULL) {
      delete point_data;
      point_data = NULL;
    }
  }
}

std::vector<std::string> CornerData::AllPointNames() {
  std::vector<std::string> names;
  std::map<std::string,PointData*>::iterator it;
  for (it = point_data_map_.begin(); it != point_data_map_.end(); it++) {
    PointData* point_data = it->second;
    names.push_back(point_data->name());
  }
  return names;
}

std::string CornerData::AddPoint(QPointF point) {

  std::string point_name = generate_point_name();
  PointData* new_point = new PointData(point_name,point);
  point_data_map_.insert(make_pair(point_name,new_point));
  return point_name;
}

std::string CornerData::generate_point_name() {
  std::map<std::string,PointData*>::iterator it;
  std::vector<std::string> used_names;
  for (it = point_data_map_.begin(); it != point_data_map_.end(); it++) {
    used_names.push_back(it->second->name());
  }

  int max_num = 0;
  for (int i = 0; i<used_names.size(); i++) {
    int num = atoi(used_names[i].c_str());
    max_num = max_num > num ? max_num : num;
  }
  char buf[32];
  memset(buf, 0, sizeof(buf));
  sprintf(buf, "%d", max_num + 1);
  return std::string(buf);
}

void CornerData::RemovePoint(std::string pointName) {
  std::map<std::string,PointData*>::iterator it = point_data_map_.find(pointName);
  if (it != point_data_map_.end()) {
    point_data_map_.erase(it);
  }
}

void CornerData::UpdatePoint(std::string pointName, QPointF point) {
  std::map<std::string, PointData*>::iterator it = point_data_map_.find(pointName);
  if (it != point_data_map_.end()) {
    it->second->set_point(point);
  }
}

PointData*  CornerData::GetPoint(std::string pointName) {
  PointData* point = NULL;
  std::map<std::string, PointData*>::iterator it = point_data_map_.find(pointName);
  if (it != point_data_map_.end()) {
    point = it->second;
  }
  return point;
}

std::string CornerData::GetPointName(QPointF point) {
  std::string point_name = "";
  std::map<std::string, PointData*>::iterator it;
  for (it = point_data_map_.begin(); it != point_data_map_.end(); it++) {
    PointData* point_data = it->second;
    if (point_data->point() == point) {
      point_name = it->first;
      break;
    }
  }
  return point_name;
}

void CornerData::AddRelatedWall(WallData* wall) {
  related_wall_map_.insert(make_pair(wall->name(),wall));
}

void CornerData::RemoveRelatedWall(WallData* wall) {
  std::string wall_name = wall->name();
  std::map<std::string,WallData* >::iterator it = related_wall_map_.find(wall_name);
  if (it != related_wall_map_.end()) {
    related_wall_map_.erase(it);
  }
}

/*
1. 包含只有一个关联墙的corner的墙
2. 和类型1的墙相接，且相接处corner只有两个关联墙
*/
void CornerData::GetUnclosedWalls(std::set<WallData*>&unclosedWalls, WallData* exclude_wall) {
  size_t related_wall_size = related_wall_map_.size();
  if (related_wall_size != 1 && related_wall_size != 2) {
    return;
  }
  if (related_wall_size == 2 && exclude_wall == NULL) {
    return;
  }
  WallData* unclosed_wall = NULL;
  std::map<std::string,WallData*>::iterator it;
  for (it = related_wall_map_.begin(); it != related_wall_map_.end(); it++) {
    if (it->second != exclude_wall) {
      unclosed_wall = it->second;
      break;
    }
  }
  unclosedWalls.insert(unclosed_wall);
  CornerData* other_corner = NULL;
  if (unclosed_wall->IsStartCorner(this)) {
    other_corner = unclosed_wall->end_corner();
  }
  else {
    other_corner = unclosed_wall->start_corner();
  }
  return other_corner->GetUnclosedWalls(unclosedWalls, unclosed_wall);
}

int CornerData::RelateWallSize(std::set<WallData*> excludeWalls) {
  int relate_wall_size = related_wall_map_.size();
  std::map<std::string,WallData*>::iterator it;
  for (it = related_wall_map_.begin(); it != related_wall_map_.end(); it++) {
    if (excludeWalls.find(it->second) != excludeWalls.end()) {
      relate_wall_size--;
    }
  }
  return relate_wall_size;
}

std::vector<WallData*> CornerData::RelateWalls() {
  std::vector<WallData*> walls; 
  std::map<std::string,WallData*>::iterator it;
  for (it = related_wall_map_.begin(); it != related_wall_map_.end(); it++) {
    walls.push_back(it->second);
  }
  return walls;
}

bool CornerData::DoContainPoint(PointData* point) {
  std::map<std::string,PointData*>::iterator it;
  for (it = point_data_map_.begin(); it != point_data_map_.end(); it++) {
    if (it->second == point) {
      return true;
    }
  }
  return false;
}

void CornerData::UpdateCornerPosition() {
  std::map<std::string,WallData*>::iterator it;
  std::vector<WallData*> walls;//,generated_line2;
  for (it = related_wall_map_.begin(); it != related_wall_map_.end(); it++) {
    WallData* wall = it->second;
	if(wall->status() != ROOM_WALL_DATA){
      continue;
	}
    LineData generated_line = wall->generate_line();
    if (wall->IsStartCorner(this) && generated_line.start_point_name() == "") {
		walls.push_back(wall);
    }
    else if(generated_line.end_point_name() == ""){
		walls.push_back(wall);
    }
  }
  int walls_size = walls.size();
  assert(walls_size == 2 || walls_size == 0);
  if(walls_size == 2) {
	LineData generate_line1 = walls[0]->generate_line();
	LineData generate_line2 = walls[1]->generate_line();
    QPointF  position = generate_line1.Intersect(generate_line2);
    std::string point_name = AddPoint(position);
	update_wall_generated_line_info(walls[0], point_name);
	update_wall_generated_line_info(walls[1], point_name);
  }

  std::map<std::string,PointData*>::iterator point_it;
  qreal x = 0;
  qreal y = 0;
  for (point_it = point_data_map_.begin(); point_it != point_data_map_.end(); point_it++) {
    QPointF position = point_it->second->point();
    x +=  position.x();
    y += position.y();
  }
  x = x/point_data_map_.size();
  y = y/point_data_map_.size();
 set_position(QVector3D(x,y,0));
}

void CornerData::update_wall_generated_line_info(WallData* wall, std::string pointName) {
	if (!wall) {
		return;
	}
	
	LineData line = wall->generate_line();
	if (wall->IsStartCorner(this)) {		
		line.set_start_point_name(pointName);
		wall->UpdateGeneratedLine(line);
	}
	else {
		line.set_end_point_name(pointName);
		wall->UpdateGeneratedLine(line);
	}
}

std::vector<CornerData*> CornerData::FindPathTo(CornerData* corner) {
  

}

std::vector<CornerData*> CornerData::NextCorners() {
  std::vector<CornerData*> next_corners;
  for (std::map<std::string, WallData*>::iterator it = related_wall_map_.begin(); it != related_wall_map_.end(); it++) {
    WallData* wall = it->second;
    if (wall->IsStartCorner(this)) {
      next_corners.push_back(wall->end_corner());
    }
    else {
      next_corners.push_back(wall->start_corner());
    }
  }
  return next_corners;
}

