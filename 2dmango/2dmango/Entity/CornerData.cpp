#include "CornerData.h"
#include "WallData.h"
#include <set>
#include <assert.h>

#include "Util/PolygonUtil.h"
#include "Util/LineUtil.h"
#include "Util/JsonUtil.h"

#include <QJsonArray>

CornerData::CornerData(): has_position_data_(false){
  generated_point_ = NULL;
}

QJsonObject CornerData::ToJson() {
  QJsonObject object;
  QJsonObject parent_object = BaseGeometryData::ToJson();
  AttachJsonObject(object, parent_object);
  QJsonArray point_array;
  for (std::map<std::string, PointData*>::iterator it = point_data_map_.begin(); it != point_data_map_.end(); it++) {
    PointData* point_data = it->second;
    QJsonObject point_data_object = point_data->ToJson();
    point_array.append(point_data_object);
  }
  object.insert("points", QJsonValue(point_array));

  QJsonArray wall_name_array;
  for (std::map<std::string, WallData*>::iterator it = related_wall_map_.begin(); it != related_wall_map_.end(); it++) {
    std::string wall_name = it->first;
    QJsonValue wall_name_value(QString(wall_name.c_str()));
    wall_name_array.append(wall_name_value);
  }
  object.insert("wall_names", QJsonValue(wall_name_array));
  if (generated_point_ == NULL) {
    object.insert("generated_point_name", QJsonValue(QString("")));
  }
  else {
    object.insert("generated_point_name", QJsonValue(QString(generated_point_->name().c_str())));
  }

  return object;
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
  if ( related_wall_map_.size() == 4) {
    int a = 0;
  }
  std::set<std::string> point_names;
  std::map<std::string,WallData*>::iterator it;
  std::vector<WallData*> walls;//,generated_line2;
  for (it = related_wall_map_.begin(); it != related_wall_map_.end(); it++) {
    WallData* wall = it->second;
    if (wall->IsStartCorner(this)) {
      if (wall->line().start_point_name() != "") {
        point_names.insert(wall->line().start_point_name());
      }

      if (wall->generate_line().start_point_name() != "") {
        point_names.insert(wall->generate_line().start_point_name());
      }
    }
    else {
      if (wall->line().end_point_name() != "") {
        point_names.insert(wall->line().end_point_name());
      }

      if (wall->generate_line().end_point_name() != "") {
        point_names.insert(wall->generate_line().end_point_name());
      }
    }

	if(wall->status() != ROOM_WALL_DATA){
      continue;
	}
    LineData generated_line = wall->generate_line();
    if (wall->IsStartCorner(this) && generated_line.start_point_name() == "") {
		walls.push_back(wall);
    }
    else if(wall->IsEndCorner(this) && generated_line.end_point_name() == ""){
		walls.push_back(wall);
    }
  }

  for (std::map<std::string, PointData*>::iterator it = point_data_map_.begin(); it != point_data_map_.end(); ) {
    if (point_names.find(it->first) == point_names.end()) {
      delete it->second;
      it->second = NULL;
      it = point_data_map_.erase(it);
    }
    else {
      it++;
    }
  }

  int walls_size = walls.size();
  assert(walls_size == 2 || walls_size == 0); 
  if(walls_size == 2) {
	LineData generate_line1 = walls[0]->generate_line();
	LineData generate_line2 = walls[1]->generate_line();
    QPointF  position = generate_line1.Intersect(generate_line2);
    assert(!position.isNull());
    //position = generate_line1.Intersect(generate_line2);
    std::string point_name = AddPoint(position);
  point_names.insert(point_name);
  generated_point_ = GetPoint(point_name);
	update_wall_generated_line_info(walls[0], point_name);
	update_wall_generated_line_info(walls[1], point_name);
  }

  for (std::map<std::string, WallData*>::iterator it = related_wall_map_.begin();
    it != related_wall_map_.end(); it++) {
    WallData* tmp_wall = it->second;
    if (tmp_wall->name() == "2") {
      int a = 0;
    }

    tmp_wall->UpdateGeneratedLine();
    tmp_wall->UpdateLine();
    //QLineF line1 = tmp_wall->line().Line();
    /*
    QLineF line2 = tmp_wall->generate_line().Line();
    if (tmp_wall->IsStartCorner(this)) {      
      std::string point_name = tmp_wall->generate_line().start_point_name();
      QLineF tmp_line(GetPoint(point_name)->point(), line2.p2());
      LineData tmp_line_data = tmp_wall->generate_line();
      tmp_line_data.set_line(tmp_line);
      tmp_wall->UpdateGeneratedLine(tmp_line_data);
    }
    else {
      std::string point_name = tmp_wall->generate_line().end_point_name();
      QLineF tmp_line(line2.p1(),GetPoint(point_name)->point());
      LineData tmp_line_data = tmp_wall->generate_line();
      tmp_line_data.set_line(tmp_line);
      tmp_wall->UpdateGeneratedLine(tmp_line_data);
    }
    line2 = tmp_wall->generate_line().Line();
    if (line2.p1() == line2.p2()) {
      int a = 0;
    }*/
  }

  //std::map<std::string,PointData*>::iterator point_it;
  std::set<std::string>::iterator point_name_it;
  qreal x = 0;
  qreal y = 0;
  for (point_name_it = point_names.begin(); point_name_it != point_names.end(); point_name_it++) {
    QPointF position = point_data_map_[*point_name_it]->point();
    x +=  position.x();
    y += position.y();
  }

  if (point_names.size() > 0) {
    x = x / point_names.size();
    y = y / point_names.size();
    set_position(QVector3D(x, y, 0));
  }
  else {
    int a = 0;
  }
  
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

std::vector<CornerData*> CornerData::FindPathTo(CornerData* corner, std::vector<CornerData*> previousPath) {
  std::vector<CornerData*> path;
  if (corner == this) {
    previousPath.push_back(this);
    return previousPath;
  }

  for (int i = 0; i < previousPath.size(); i++) {
    CornerData* tmp_corner = previousPath[i];
    if (tmp_corner == this) {
      return path;
    }
  }
  CornerData* previous_corner = NULL;
  if (previousPath.size() > 0) {
    previous_corner = previousPath[previousPath.size() - 1];
  }
  previousPath.push_back(this);
  std::vector<std::vector<CornerData*>> paths;
  std::vector<CornerData*> next_corners = NextCorners();
  for (int i = 0; i < next_corners.size(); i++) {
    CornerData* next_corner = next_corners[i];
    if (next_corner == previous_corner) {
      continue;
    }
    std::vector<CornerData*> tmp_path = next_corner->FindPathTo(corner, previousPath);
    if (tmp_path.size() > 0) {
      paths.push_back(tmp_path);
    }
  }

  if (paths.size() == 0) {
    return path;
  }

  path = paths[0];
  for (int i = 1; i < paths.size(); i++) {
    std::vector<CornerData*> tmp_path = paths[i];
    if (path_included_in(tmp_path, path)) {
      path = tmp_path;
    }
  }
  return path;
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

std::vector<QPointF> CornerData::get_points(std::vector<CornerData*> corners) {
  std::vector<QPointF> points;
  for (std::vector<CornerData*>::iterator it = corners.begin(); it != corners.end(); it++) {
    CornerData* corner = *it;
    assert(corner->RelateWalls().size() > 0);
    WallData* wall = corner->RelateWalls()[0];
    if (wall->IsStartCorner(corner)) {
      points.push_back(corner->GetPoint(wall->line().start_point_name())->point());
    }
    else {
      std::string end_corner_name = wall->line().end_point_name();
      PointData* point_data = corner->GetPoint(end_corner_name);
      QPointF point = point_data->point();
      points.push_back(corner->GetPoint(wall->line().end_point_name())->point());
    }
  }
  return points;
}

bool CornerData::path_included_in(std::vector<CornerData*> path1, std::vector<CornerData*> path2) {
  std::set<CornerData*> set1, set2,extra_set;
  std::vector<CornerData*> extra_corners;
  set1.insert(path1.begin(), path1.end());
  set2.insert(path2.begin(), path2.end());
  for (std::set<CornerData*>::iterator it = set1.begin(); it != set1.end(); it++) {
    if (set2.find(*it) == set2.end()) {
      extra_corners.push_back(*it);
    }
  }

  std::vector<QPointF> points2 = get_points(path2);
  std::vector<QPointF> extra_points = get_points(extra_corners);
  for (int i = 0; i < extra_points.size();i++) {
    QPointF extra_point = extra_points[i];
    if (!IsPointInPolygon(extra_point, points2)) {
      false;
    }
  }
  return true;
}

QPointF CornerData::LikePosition() {
  QPointF position;
  if (related_wall_map_.size() == 0) {
    return position;
  }
  WallData* wall = related_wall_map_.begin()->second;
  if (wall->IsStartCorner(this)) {
    position = wall->start_corner_position();
  }
  else {
    position = wall->end_corner_position();
  }
  return position;
}

std::vector<QPointF> CornerData::GetAvailableStartPoints() {
  std::vector<QPointF> points;
  WallData* first_wall = related_wall_map_.begin()->second;
  for (std::map<std::string, WallData*>::iterator it = related_wall_map_.begin(); it != related_wall_map_.end(); it++) {
    WallData* wall = it->second;
    if (wall == first_wall) {
      continue;
    }
    
    QLineF line1 = first_wall->line().Line();
    QLineF line2 = first_wall->generate_line().Line();
    QLineF line3 = wall->line().Line();
    QLineF line4 = wall->generate_line().Line();

    QPointF point1;
    if (line1.intersect(line4, &point1) != QLineF::NoIntersection) {
      PointData* point_data = find_point_with_position(point1);
      if (point_data == NULL) {
        points.push_back(point1);
      }
    }

    QPointF point2;
    if (line2.intersect(line3, &point2) != QLineF::NoIntersection) {
      PointData* point_data = find_point_with_position(point2);
      if (point_data == NULL) {
        points.push_back(point2);
      }
    }

  }
  
  PointData* outside_point = OutsidePoint();
  if (outside_point != NULL) {
    points.push_back(outside_point->point());
  }

  return points;
}

PointData* CornerData::find_point_with_position(QPointF position) {
  PointData* point = NULL;
  for (std::map<std::string, PointData*>::iterator it = point_data_map_.begin(); it != point_data_map_.end(); it++) {
    QPointF tmp_point = it->second->point();
    if (QVector2D(position - tmp_point).length() < 0.01) {
      point = it->second;
      break;
    }
  }
  return point;
}

PointData* CornerData::OutsidePoint() {
  PointData* outside_point = NULL;
  for (std::map<std::string, PointData*>::iterator it = point_data_map_.begin(); it != point_data_map_.end(); it++) {
    std::string point_name = it->first;
    int inside_index = 0;
    int outside_index = 0;
    for (std::map<std::string, WallData*>::iterator wall_it = related_wall_map_.begin(); wall_it != related_wall_map_.end(); wall_it++) {
      WallData* wall = wall_it->second;
      if (wall->line().start_point_name() == point_name || wall->line().end_point_name() == point_name) {
        inside_index++;
      }
      if (wall->generate_line().start_point_name() == point_name || wall->generate_line().end_point_name() == point_name) {
        outside_index++;
      }
    }
  
    if (inside_index == 0 && outside_index == 2) {
      outside_point = it->second;
      break;
    }
  }

  return outside_point;
}

void CornerData::UpdateRelatedInfo() {  

  std::vector<std::string> point_names;
  for (std::map<std::string, WallData*>::iterator it = related_wall_map_.begin(); it != related_wall_map_.end(); it++) {
    WallData* wall = it->second;
    LineData line = wall->line();
    LineData generate_line = wall->generate_line();
    

    for (std::map<std::string, PointData*>::iterator point_it = point_data_map_.begin(); point_it != point_data_map_.end(); point_it++) {
      PointData* point = point_it->second;
      if (line.IsAvailable()) {
        QPointF point_position = point->point();
        QLineF line_ = line.Line();
        if (IsPointInLine(point_position, line_)) {
          if (wall->IsStartCorner(this)) {
            if (point->name() != wall->line().start_point_name()) {
              point_names.push_back(wall->line().start_point_name());
              wall->set_line_start_name(point->name());
            }
          }
          else {
            if (point->name() != wall->line().end_point_name()) {
              point_names.push_back(wall->line().end_point_name());
              wall->set_line_end_name(point->name());
            }
          }
        }
      }

      if (generate_line.IsAvailable()) {
        QPointF point_position = point->point();
        QLineF line_ = generate_line.Line();
        if (IsPointInLine(point_position, line_)) {
          if (wall->IsStartCorner(this)) {
            if (point->name() != wall->generate_line().start_point_name()) {
              point_names.push_back(wall->generate_line().start_point_name());
              wall->set_generated_line_start_name(point->name());
            }
          }
          else {
            if (point->name() != wall->generate_line().end_point_name()) {
              point_names.push_back(wall->generate_line().end_point_name());
              wall->set_generated_line_end_name(point->name());
            }
          }
        }
      }

    }
  }

  for (int i = 0; i < point_names.size(); i++) {
    std::string point_name = point_names[i];
    for (std::map<std::string, WallData*>::iterator it = related_wall_map_.begin(); it != related_wall_map_.end(); it++) {
      WallData* wall = it->second;
      LineData line = wall->line();
      LineData generate_line = wall->generate_line();
      if (wall->IsStartCorner(this)) {
        if (line.start_point_name() == point_name) {
          wall->set_line_start_name("");
        }
        
        if (generate_line.start_point_name() == point_name) {
          wall->set_generated_line_start_name("");
        }
      }
      else {
        if (line.end_point_name() == point_name) {
          wall->set_line_end_name("");
        }

        if (generate_line.end_point_name() == point_name) {
          wall->set_generated_line_end_name("");
        }
      }
    }
  }

  
}

void CornerData::update_wall_relate_info(WallData* wallData,PointData* point) {
  QPointF point_position = point->point();
  
}

PointData* CornerData::FindConnectPoint(WallData* wall1, WallData* wall2) {
  PointData* point = NULL;
  
  return point;
}

