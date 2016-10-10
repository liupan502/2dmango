#include "DesignDataWrapper.h"
#include "Geometry/DoubleDoorGeometry.h"
#include "Geometry/SingleDoorGeometry.h"
#include "Geometry/MoveDoorGeometry.h"
#include "Geometry/WindowGeometry.h"

DesignDataWrapper* DesignDataWrapper::instance = 0;

DesignDataWrapper::DesignDataWrapper(){
  design_data_ = new DesignData();
  hot_region_ = HotRegionGeometry(QPointF(100.0,100.0),50,50);
  current_selected_geometry_ = NULL;
}

void DesignDataWrapper::Draw(QPainter* painter){
  hot_region_.Draw(painter);
  for (int i = 0; i < auxiliary_lines_.size(); i++) {
    auxiliary_lines_[i].Draw(painter);
  }
  for(int i=0;i<wall_geometrys_.size();i++){
    wall_geometrys_[i].Draw(painter);
  }

  if (current_selected_geometry_ != NULL) {
    current_selected_geometry_->Draw(painter);
  }
}

DesignDataWrapper*  DesignDataWrapper::GetInstance(){
  
  if(instance == NULL){
    instance = new DesignDataWrapper();
  }  
  return instance;
}

CornerData* DesignDataWrapper::AddCorner(){
  return design_data_->AddCorner();
}

std::string DesignDataWrapper::AddWall(std::string cornerName1, std::string cornerName2){
  return "wall name";
}

std::string DesignDataWrapper::AddRoom(std::vector<std::string> cornerNames){
  return "room name";
}

WallData* DesignDataWrapper::AddWall(){
  return design_data_->AddWall();
}

void DesignDataWrapper::UpdateGeometry() {
  wall_geometrys_ = design_data_->ComputeWallGeometrys();
}

bool DesignDataWrapper::FindConnectedPoints(QPointF currentPoint, std::string wallName, std::vector<QPointF>& points) {
  return design_data_->FindConnectedPoints(currentPoint, wallName,points);
}

void DesignDataWrapper::AddAuxiliaryLine(QPointF point1, QPointF point2) {
  AuxiliaryLineGeometry auxiliary_line(point1,point2);
  auxiliary_lines_.push_back(auxiliary_line);    
}

void DesignDataWrapper::ClearAuxiliaryLines(){
  auxiliary_lines_.clear();
}

bool DesignDataWrapper::FindAttachedCorner(QPointF currentPoint, std::string wallName, std::vector<CornerData*>& points) {
  return design_data_->FindAttachedCorner(currentPoint,wallName,points);
}

QPointF DesignDataWrapper::CornerPosition(std::string cornerName) {
  return design_data_->CornerPosition(cornerName);
}

void DesignDataWrapper::UpdateRoomInfo() {
  design_data_->UpdateRoomInfo();
  design_data_->UpdateGeometry();
}

bool DesignDataWrapper::FindStartPoint(QPointF currentPoint, QPointF& startPoint) {
  return design_data_->FindStartPoint(currentPoint, startPoint);
}

bool DesignDataWrapper::IsEmpty() {
  return design_data_->IsEmpty();
}

CornerData* DesignDataWrapper::FindCornerWithPosition(QPointF currentPosition) {
  return design_data_->FindCornerWithPosition(currentPosition);
}

bool DesignDataWrapper::FindEndPoint(WallData* wall_data, CornerData* corner, QPointF currentPoint, QPointF& endPoint) {
  return design_data_->FindEndPoint(wall_data,corner, currentPoint, endPoint);
}

void DesignDataWrapper::AddGeometry(BaseGeometry* geometry) {
  delete_current_selected_geometry();
  current_selected_geometry_ = geometry;
}

BaseGeometry* DesignDataWrapper::current_selected_geometry() {
  return current_selected_geometry_;
}

void DesignDataWrapper::delete_current_selected_geometry() {
  if (current_selected_geometry_ != NULL) {
    delete current_selected_geometry_;
    current_selected_geometry_ = NULL;
  }
}

bool DesignDataWrapper::GetClosestWall(QPointF position, qreal& distance, WallGeometry& wallGeometry) {  
  qreal min_distance = -1;
  for (int i = 0; i < wall_geometrys_.size(); i++) {
    WallGeometry tmp_wall_geometry = wall_geometrys_[i];
    qreal tmp_distance;
    if (tmp_wall_geometry.PointDistanceToGeometry(position, tmp_distance)) {
      if (min_distance < 0) {
        wallGeometry = tmp_wall_geometry;
        min_distance = tmp_distance;
      }
      else if (tmp_distance < min_distance) {
        wallGeometry = tmp_wall_geometry;
        min_distance = tmp_distance;
      }
    }
  }

  if (min_distance < 0) {
    return false;
  }
  else {    
    distance = min_distance;
    return true;
  }
}

void DesignDataWrapper::AddCurrentData() {
  GEOMETRY_TYPE geometry_type = current_selected_geometry_->geometry_type();
  switch (geometry_type) {
    case GEOMETRY_OPENING:
      insert_opening_data((InnerWallGeometry*)current_selected_geometry_);
      break;
    default:
      break;
  }
}

void DesignDataWrapper::insert_opening_data(InnerWallGeometry* geometry) {
  OPENING_TYPE opening_type = geometry->opening_type();
  std::string opening_name = design_data_->GenerateOpeningName();
  OpeningData* data = NULL;
  switch (opening_type) {
    case OPENING_SINGLE_DOOR:
      data = new OpeningData(*(SingleDoorGeometry*)geometry, opening_name);
      break;
    case OPENING_MOVE_DOOR:
      data = new OpeningData(*((MoveDoorGeometry*)geometry), opening_name);
      break;
    case OPENING_DOUBLE_DOOR:
      data = new OpeningData(*(DoubleDoorGeometry*)geometry, opening_name);
      break;
    case OPENING_WINDOW:
      data = new OpeningData(*(WindowGeometry*)geometry, opening_name);
      break;
    default:
      break;
  }

  if (data != NULL) {
    design_data_->AddOpening(data);
  }  
}

