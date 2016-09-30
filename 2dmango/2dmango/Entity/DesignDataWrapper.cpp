#include "DesignDataWrapper.h"

DesignDataWrapper* DesignDataWrapper::instance = 0;

DesignDataWrapper::DesignDataWrapper(){
  design_data_ = new DesignData();
  hot_region_ = HotRegionGeometry(QPointF(100.0,100.0),50,50);
}

void DesignDataWrapper::Draw(QPainter* painter){
  hot_region_.Draw(painter);
  for (int i = 0; i < auxiliary_lines_.size(); i++) {
    auxiliary_lines_[i].Draw(painter);
  }
  for(int i=0;i<wall_geometrys_.size();i++){
    wall_geometrys_[i].Draw(painter);
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


