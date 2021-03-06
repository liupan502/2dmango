#include "WallData.h"
#include <QLineF>
#include "CornerData.h"
#include "RoomData.h"
#include "Geometry/WallGeometry.h"
#include <assert.h>
#include <QJsonArray>

QJsonObject WallData::ToJson() {
  QJsonObject object;
  QJsonObject parent_object = BaseGeometryData::ToJson();
  AttachJsonObject(object, parent_object);
  object.insert("wall_data_type", QJsonValue((int)(data_type_)));
  object.insert("wall_data_status", QJsonValue((int)(status_)));

  QJsonObject line_object = line_.ToJson();
  object.insert("line", QJsonValue(line_object));

  QJsonObject generated_line_object = generated_line_.ToJson();
  object.insert("generated_line", QJsonValue(generated_line_object));

  if (start_corner_ == NULL) {
    object.insert("start_corner_name", QJsonValue(""));
  }
  else {
    object.insert("start_corner_name", QJsonValue(QString(start_corner_->name().c_str())));
  }

  if (end_corner_ == NULL) {
    object.insert("end_corner_name", QJsonValue(""));
  }
  else {
    object.insert("end_corner_name", QJsonValue(QString(end_corner_->name().c_str())));
  }

  QString normal_vector_str = QVector2DToString(normal_vector_);
  object.insert("normal_vector", QJsonValue(normal_vector_str));

  QJsonArray opening_name_array;
  for (std::set<std::string>::iterator it = opening_names_.begin(); it != opening_names_.end(); it++) {
    std::string opening_name = *it;
    QJsonValue opening_name_value(QString(opening_name.c_str()));
    opening_name_array.append(opening_name_value);
  }
  object.insert("opening_names", QJsonValue(opening_name_array));
  return object;
}

void WallData::InitWithObject(QJsonObject& jsonObject) {
  BaseGeometryData::InitWithObject(jsonObject);
  
  if (jsonObject.contains("wall_data_type")) {
    data_type_ = (WALL_DATA_TYPE)jsonObject["wall_data_type"].toInt();
  }
  else {
    data_type_ = WALL_NO_DATA;
  }

  if (jsonObject.contains("wall_data_status")) {
    status_ = (WALL_DATA_STATUS)jsonObject["wall_data_status"].toInt();
  }
  else {
    status_ = NONE_STAUS_WALL_DATA;
  }

  if (jsonObject.contains("line")) {
    QJsonObject line_object = jsonObject["line"].toObject();
    line_.InitWithObject(line_object);
  }

  if (jsonObject.contains("generated_line")) {
    QJsonObject generated_line_object = jsonObject["generated_line"].toObject();
    generated_line_.InitWithObject(generated_line_object);
  }

  if (jsonObject.contains("start_corner_name")) {
    std::string start_corner_name = jsonObject["start_corner_name"].toString().toStdString();
    start_corner_ = new CornerData();
    start_corner_->set_name(start_corner_name);
  }

  if (jsonObject.contains("end_corner_name")) {
    std::string end_corner_name = jsonObject["end_corner_name"].toString().toStdString();
    end_corner_ = new CornerData();
    end_corner_->set_name(end_corner_name);
  }

  if (jsonObject.contains("normal_vector")) {
    QString normal_vector_str = jsonObject["normal_vector"].toString();
    normal_vector_ = StringToQVector2D(normal_vector_str);
  }

  if (jsonObject.contains("opening_names")) {
    QJsonArray opening_name_array = jsonObject["opening_names"].toArray();
    for (int i = 0; i < opening_name_array.size(); i++) {
      std::string opening_name = opening_name_array[i].toString().toStdString();
      opening_names_.insert(opening_name);
    }
  }

}

void WallData::update_corner_data(CornerData** cornerData, std::map<std::string, CornerData*>& cornerDataMap) {
  if (cornerData == NULL || (*cornerData) == NULL) {
    return;
  }
  std::string corner_name = (*cornerData)->name();
  std::map<std::string, CornerData*>::iterator it = cornerDataMap.find(corner_name);
  if (it != cornerDataMap.end()) {
    CornerData* tmp_corner = it->second;
    if (tmp_corner != (*cornerData)) {
      delete (*cornerData);
      (*cornerData) = tmp_corner;
    }
  }
}

void WallData::UpdateCorners(std::map<std::string, CornerData*>& cornerDataMap) {
  if (start_corner_ != NULL) {
    update_corner_data(&start_corner_, cornerDataMap);
  }

  if (end_corner_ != NULL) {
    update_corner_data(&end_corner_, cornerDataMap);
  }
}

bool WallData::IsStartCorner(CornerData* corner){
  if (corner == NULL) {
    return false;
  }
  return (start_corner() == corner);
}

bool WallData::IsEndCorner(CornerData* corner){
  if (corner == NULL) {
    return false;
  }
  return (end_corner() == corner);
}

bool WallData::DoContainCorner(CornerData* corner){
  return (IsStartCorner(corner) || IsEndCorner(corner));
}

QVector2D WallData::WallVector() {
  return QVector2D(end_corner_position() - start_corner_position());
}

QVector2D WallData::WallPerpendicularVector() {
  QVector2D wall_vector = WallVector();
  return QVector2D(wall_vector.y(),-wall_vector.x());
}

QLineF WallData::WallLine() {  
  return QLineF(start_corner_position(), end_corner_position());
}

std::vector<std::string> WallData::AllLineNames() {
  std::vector<std::string> names;
  if (line_.name() != "") {
    names.push_back(line_.name());
  }

  if (generated_line_.name() != "") {
    names.push_back(generated_line_.name());
  }
  return names;
}

void WallData::set_start_corner(CornerData* corner) {
  if (start_corner_ != NULL) {
    start_corner_->RemoveRelatedWall(this);
    line_.set_start_point_name("");
    generated_line_.set_start_point_name("");
  }
  start_corner_ = corner;
  start_corner_->AddRelatedWall(this);
}

CornerData* WallData::start_corner() {
  return start_corner_;
}

void WallData::set_end_corner(CornerData* corner) {
  if (end_corner_ != NULL) {
    end_corner_->RemoveRelatedWall(this);
    line_.set_end_point_name("");
    generated_line_.set_end_point_name("");
  }
  end_corner_ = corner;
  end_corner_->AddRelatedWall(this);
}

CornerData* WallData::end_corner() {
  return end_corner_;
}

void WallData::set_start_corner_position(QPointF point) {
  if (start_corner_ == NULL) {
    return;
  }
  if (line_.start_point_name() == "") {
    std::string point_name = start_corner_->GetPointName(point);
    
    if (point_name == "") {
      point_name = start_corner_->AddPoint(point);
    }    
    line_.set_start_point_name(point_name);
  }
  start_corner_->UpdatePoint(line_.start_point_name(),point);
  QLineF line = line_.Line();
  line_.set_line(QLineF(point, line.p2()));
}

void WallData::set_end_corner_position(QPointF point) {
  if (end_corner_ == NULL) {
    return;
  }
  
  if (line_.end_point_name() == "") {
    std::string point_name = end_corner_->GetPointName(point);
    if (point_name == "") {
      point_name = end_corner_->AddPoint(point);      
    }
    line_.set_end_point_name(point_name);
  }
  end_corner_->UpdatePoint(line_.end_point_name(), point);
  QLineF line = line_.Line();
  line_.set_line(QLineF(line.p1(), point));
}

QPointF WallData::start_corner_position() {
  QPointF position;
  if (start_corner_ == NULL) {
    return position;
  }
  if (line_.start_point_name() == "") {
    return position;
  }
  position = start_corner_->GetPoint(line_.start_point_name())->point();
  return position;
}

QPointF WallData::end_corner_position() {
  QPointF position;
  if (end_corner_ == NULL) {
    return position;
  }
  if (line_.end_point_name() == "") {
    return position;
  }
  position = end_corner_->GetPoint(line_.end_point_name())->point();
  return position;
}

std::string WallData::start_corner_name() {
  std::string corner_name = "";
  if (start_corner_ ) {
    corner_name = start_corner_->name();
  }
  return corner_name;
}

std::string WallData::end_corner_name() {
  std::string corner_name = "";
  if (end_corner_) {
    corner_name = end_corner_->name();
  }
  return corner_name;
}

bool WallData::IsUnsharedWall(std::set<WallData*> excludeWalls) {
  int size1 = start_corner_->RelateWallSize(excludeWalls);
  int size2 = end_corner_->RelateWallSize(excludeWalls);
  if (size1 == 2 || size2 == 2) {
    return true;
  }
  return false;
}
/*
RoomData* WallData::GetRoom(std::set<WallData*> excludeWalls) {
  RoomData* room = NULL;
  int size = start_corner_->RelateWallSize(excludeWalls);
  CornerData* first_corner = NULL;
  if (size == 2) {
    first_corner = start_corner_;
  }
  else if (end_corner_->RelateWallSize(excludeWalls)) {
    first_corner = end_corner_;
  }
  if (first_corner == NULL) {
    return;
  }
  return room;
}
*/

std::vector<WallData*> WallData::GetRoom(std::set<WallData*> excludeWalls,std::vector<WallData*> currentPath ) {
  std::vector<WallData*> room = std::vector<WallData*>();
  std::vector<std::vector<WallData*>> rooms;
  if (currentPath.size() == 0 && !IsUnsharedWall(excludeWalls)) {
    return room;
  }
  currentPath.push_back(this);
  if (! is_available_path(currentPath)) {
    return room;
  }
  if (is_room_path(currentPath)) {    
	  rooms.push_back(currentPath);
  }
  else {
    CornerData* last_corner = find_last_corner(currentPath);
    std::vector<WallData*> walls = last_corner->RelateWalls();
    for (int i = 0; i < walls.size(); i++) {
      WallData* wall = walls[i];
      if (excludeWalls.find(wall) != excludeWalls.end()) {
        continue;
      }
      if (wall == this) {
        continue;
      }
      std::vector<WallData*> tmp_room = wall->GetRoom(excludeWalls,currentPath);
      if (tmp_room.size() > 0) {        
		    rooms.push_back(tmp_room);
        
      }
    }
  }

  if (rooms.size() > 0) {
    if (rooms.size() > 1) {
      int a = 0;
    }
	  RoomData room_data("",rooms[0]);
    for (int i = 1; i < rooms.size(); i++) {
      RoomData tmp_room_data("", rooms[i]);
      if (tmp_room_data.IsIncludedIn(room_data)) {
        room_data = tmp_room_data;
      }      
    }
    room = room_data.walls();
  }  
  return room;
}

bool WallData::is_available_path(std::vector<WallData*> wallPath) {
  
  if (wallPath.size() == 0) {
    return true;
  }
  std::vector<CornerData*> corner_path;
  CornerData* previous_corner = wallPath[0]->end_corner();
  corner_path.push_back(previous_corner);
  for (int i = 1; i < wallPath.size(); i++) {
    WallData* wall = wallPath[i];
    if (wall->IsEndCorner(previous_corner)) {      
      previous_corner = wall->start_corner();
    }
    else {      
      previous_corner = wall->end_corner();
    }
    corner_path.push_back(previous_corner);
  }
  std::set<CornerData*> corners_set;
  corners_set.insert(corner_path.begin(),corner_path.end());
  if(corners_set.size() == corner_path.size()){ 
    return true;
  }
  else {
    return false;
  }
}

bool WallData::is_room_path(std::vector<WallData*> wallPath) {
  int wall_size = wallPath.size();
  if (wall_size < 3) {
    return false;
  }
  WallData* wall1 = wallPath[wall_size-2];
  WallData* wall2 = wallPath[wall_size-1];
  CornerData* first_corner = wallPath[0]->start_corner();
  CornerData* last_corner = find_last_corner(wallPath); 
  if (first_corner == last_corner) {
    return true;
  }
  else {
    return false;
  }
}

CornerData* WallData::find_last_corner(std::vector<WallData*> wallPath) {
  CornerData* next_corner = NULL;
  int wall_size = wallPath.size();
  if (wall_size == 1) {
    next_corner = wallPath[0]->end_corner();
  }
  else if (wall_size > 1) {
    WallData* wall1 = wallPath[wall_size-2];
    WallData* wall2 = wallPath[wall_size-1];
    if (wall1->DoContainCorner(wall2->start_corner())) {
      next_corner = wall2->end_corner();
    }
    else {
      next_corner = wall2->start_corner();
    }
  }

  return next_corner;
}

LineData WallData::line() {
  return line_;
}

LineData WallData::generate_line() {
  return generated_line_;
}

bool WallData::IsInsideConnected(WallData* wall) {
  bool result = true;

  return result;
}

void WallData::ResetGeometry(){
  normal_vector_ = QVector2D();  
  if (true) {
    PointData* point = start_corner_->GetPoint(generated_line_.start_point_name());
	  if (point != NULL) {
      point->Reset();
	  }    
  }

  if (true) {
    PointData* point = end_corner_->GetPoint(generated_line_.end_point_name());
	  if (point != NULL) {
		  point->Reset();
	  }    
  }
}

PointData* WallData::GetConnectedPoint(WallData* wall) {
  PointData* point = NULL;
  CornerData* corner = GetConnectedCorner(wall);
  if (!corner) {
    return point;
  }
  if (IsStartCorner(corner)) {
    if (wall->IsStartCorner(corner)) {      
      point = start_start_connected_position(wall, corner);	  
    }
    else {
      point = start_end_connected_position(wall, corner);
    }
  }
  else {
    if (wall->IsEndCorner(corner)) {
		point = end_end_connected_position(wall, corner);
    }
    else {
		point = end_start_connected_position(wall, corner);
    }
  }
  return point;
}

CornerData* WallData::GetConnectedCorner(WallData* wall) {
  CornerData* connected_corner = NULL;
  if (DoContainCorner(wall->start_corner())) {
    connected_corner = wall->start_corner();
  }
  else if (DoContainCorner(wall->end_corner())) {
    connected_corner = wall->end_corner();
  }
  return connected_corner;
}

PointData* WallData::start_start_connected_position(WallData* startCornerWall, CornerData* corner) {
  PointData* point = NULL;
  LineData other_line = startCornerWall->line();
  LineData other_generate_line = startCornerWall->generate_line();

  std::string name1 = line_.start_point_name();
  std::string generate_name1 = generated_line_.start_point_name();
  std::string name2 = other_line.start_point_name();
  std::string generate_name2 = other_generate_line.start_point_name();
  point = compute_connected_position(corner, startCornerWall,name1, generate_name1, name2, generate_name2);
  return point;
}

PointData* WallData::start_end_connected_position(WallData* endCornerWall, CornerData* corner) {
  PointData* point = NULL;
  LineData other_line = endCornerWall->line();
  LineData other_generate_line = endCornerWall->generate_line();

  std::string name1 = line_.start_point_name();
  std::string generate_name1 = generated_line_.start_point_name();
  std::string name2 = other_line.end_point_name();
  std::string generate_name2 = other_generate_line.end_point_name();
  point = compute_connected_position(corner, endCornerWall, name1, generate_name1, name2, generate_name2);
  return point;
}

PointData* WallData::end_start_connected_position(WallData* startCornerWall, CornerData* corner) {
  PointData* point = NULL;
  LineData other_line = startCornerWall->line();
  LineData other_generate_line = startCornerWall->generate_line();

  std::string name1 = line_.end_point_name();
  std::string generate_name1 = generated_line_.end_point_name();
  std::string name2 = other_line.start_point_name();
  std::string generate_name2 = other_generate_line.start_point_name();
  point = compute_connected_position(corner, startCornerWall, name1, generate_name1, name2, generate_name2);
  return point;
}

PointData* WallData::end_end_connected_position(WallData* endCornerWall, CornerData* corner) {
  PointData* point = NULL;
  LineData other_line = endCornerWall->line();
  LineData other_generate_line = endCornerWall->generate_line();

  std::string name1 = line_.end_point_name();
  std::string generate_name1 = generated_line_.end_point_name();
  std::string name2 = other_line.end_point_name();
  std::string generate_name2 = other_generate_line.end_point_name();
  point = compute_connected_position(corner, endCornerWall, name1, generate_name1, name2, generate_name2);
  return point;
}

PointData* WallData::compute_connected_position(CornerData* corner, WallData* wall, std::string name1, std::string generateName1,
  std::string name2, std::string generateName2) {
  PointData* point = NULL;
  LineData other_line = wall->line();
  LineData other_generate_line = wall->generate_line();
  if (name1 == name2) {
    point = corner->GetPoint(name1);
  }
  else if (name1 == generateName2) {
    point = corner->GetPoint(name1);
    QPointF position = line_.Intersect(other_generate_line);
    point->set_point(position);
  }
  else if (generateName1 == name2) {
    point = corner->GetPoint(name2);
    QPointF position = generated_line_.Intersect(other_line);
    point->set_point(position);
  }
  else {
    point = corner->GetPoint(generateName1);
    QPointF position = generated_line_.Intersect(other_generate_line);
    //assert()
    point->set_point(position);
  }
  return point;
}

void WallData::set_normal_vector(QVector2D vector) {
  if (vector.isNull()){
    return;
  }
  PointData* start_point = start_corner()->GetPoint(line_.start_point_name());
  PointData* end_point = end_corner()->GetPoint(line_.end_point_name());
  QVector2D line_vector = QVector2D(start_point->point() - end_point->point());
  qreal value = line_vector.x()*vector.x() + line_vector.y()*vector.y();
  //assert(value == 0);
  if (abs(value) < 0.001 ) {
    vector.normalize();
    vector = vector*width();
    normal_vector_ = vector;    
    QLineF line = line_.Line();
    QLineF generated_line = line.translated(vector.x(),vector.y());
    generated_line_.set_line(generated_line);
  }
}

QVector2D WallData::normal_vector() {
  return normal_vector_;
}

void WallData::ComputePoint(PointData* point) {
  CornerData* corner = NULL;
  if(start_corner_->DoContainPoint(point) ) {
    corner = start_corner_;
  }
  else if (end_corner_->DoContainPoint(point)) {
    corner = end_corner_;
  }

  if (corner == NULL) {
    return;
  }

  std::vector<WallData*> walls = corner->RelateWalls();
  WallData* other_wall = NULL;
  for (int i = 0; i < walls.size(); i++) {
    if (walls[i] == this) {
      continue;
    }
    if (walls[i]->DoContianPoint(point)) {
      other_wall = walls[i];
      break;
    }
  }

  if (other_wall == NULL) {
    return;
  }

  /*LineData line = GetLine(point);
  LineData other_line = other_wall->GetLine(point);
  if (line.Line().isNull() || other_line.Line().isNull()) {
    return;
  }
  QPointF position = line.Intersect(other_line);
  if (position.isNull()) {
    return;
  }*/
  point = this->GetConnectedPoint(other_wall);
  //point->set_point(position);
}

bool WallData::DoContianPoint(PointData* point) {
  bool result = false;
  if (point == NULL|| point->name() == "") {
    return result;
  }
  /*if (start_corner_->DoContainPoint(point) || end_corner_->DoContainPoint(point)){
    result = true;
  }*/

  std::string point_name = point->name();
  if (start_corner_->DoContainPoint(point)) {
    if (point_name == line_.start_point_name()) {
      result = true;
    }

    if (point_name == generated_line_.start_point_name()) {
      result = true;
    }
  }
  else if(end_corner_->DoContainPoint(point)){
    if (point_name == line_.end_point_name()) {
      result = true;
    }

    if (point_name == generated_line_.end_point_name()) {
      result = true;
    }
  }
  return result;
}

LineData WallData::GetLine(PointData* point) {
  LineData line;
  if (point == NULL || point->name() == "") {
    return line;
  }
  std::string point_name = point->name();
  if (point_name == line_.start_point_name() || point_name == line_.end_point_name()) {
    line = line_;
  }
  else if (point_name == generated_line_.start_point_name() || point_name == generated_line_.end_point_name()) {
    line = generated_line_;
  }
  return line;
}

void WallData::UpdateGeneratedLine(LineData line) {
	generated_line_ = line;
}

WallGeometry WallData::GetGeometry() {
  std::vector<QPointF> points;
  if (status_ == ROOM_WALL_DATA || status_ == UNROOM_WALL_DATA) {
    points.push_back(start_corner_->GetPoint(generated_line_.start_point_name())->point());
    points.push_back(QPointF(start_corner_->position().x(), start_corner_->position().y()));
    points.push_back(start_corner_->GetPoint(line_.start_point_name())->point());
    points.push_back(end_corner_->GetPoint(line_.end_point_name())->point());
    points.push_back(QPointF(end_corner_->position().x(), end_corner_->position().y()));
    points.push_back(end_corner_->GetPoint(generated_line_.end_point_name())->point());
  }
  else {
    points.push_back(start_corner_position());
    points.push_back(end_corner_position());
  }
  WallGeometry geometry(points,this);
  return geometry;
}

void WallData::set_status(WALL_DATA_STATUS status) {
	status_ = status;
}

WALL_DATA_STATUS WallData::status() {
	return status_;
}

void WallData::set_line_start_name(std::string name) {
  line_.set_start_point_name(name);
}

void WallData::set_line_end_name(std::string name) {
  line_.set_end_point_name(name);
}

void WallData::set_generated_line_start_name(std::string name) {
  generated_line_.set_start_point_name(name);  
}

void WallData::set_generated_line_end_name(std::string name) {
  generated_line_.set_end_point_name(name);
}

void WallData::UpdateLine() {
  if (start_corner_ != NULL) {
    PointData* start_point = start_corner_->GetPoint(line_.start_point_name());
    if (start_point != NULL && !start_point->point().isNull()) {
      assert(!start_point->point().isNull());
      QLineF  line(start_point->point(), line_.Line().p2());
      assert(line.p1() != line.p2());
      line_.set_line(line);
    }
  }

  if (end_corner_ != NULL) {
    PointData* end_point = end_corner_->GetPoint(line_.end_point_name());
    if (end_point != NULL && !end_point->point().isNull()) {
      assert(!end_point->point().isNull());
      QLineF line(line_.Line().p1(), end_point->point());
      assert(line.p1() != line.p2());
      line_.set_line(line);
    }
  }
  
}

void WallData::UpdateGeneratedLine() {
  if (start_corner_ != NULL) {
    PointData* start_point = start_corner_->GetPoint(generated_line_.start_point_name());
    if (start_point != NULL && !start_point->point().isNull()) {
      assert(!start_point->point().isNull());
      QLineF line(start_point->point(), generated_line_.Line().p2());
      assert(line.p1() != line.p2());
      generated_line_.set_line(line);
    }
  }

  if (end_corner_ != NULL) {
    PointData* end_point = end_corner_->GetPoint(generated_line_.end_point_name());
    if (end_point != NULL && !end_point->point().isNull()) {
      
      QLineF line(generated_line_.Line().p1(), end_point->point());
      assert(line.p1() != line.p2());
      generated_line_.set_line(line);
    }

  }
}

void WallData::AddOpening(std::string opening_name) {
  opening_names_.insert(opening_name);
}

void WallData::RemoveOpening(std::string opening_name) {
  std::set<std::string>::iterator it = opening_names_.find(opening_name);
  if (it != opening_names_.end()) {
    opening_names_.erase(it);
  }
}

std::set<std::string> WallData::opening_names() {
  return opening_names_;
}



