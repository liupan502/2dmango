#include "DesignDataWrapper.h"
#include "Geometry/DoubleDoorGeometry.h"
#include "Geometry/SingleDoorGeometry.h"
#include "Geometry/MoveDoorGeometry.h"
#include "Geometry/WindowGeometry.h"
#include "Geometry/ModelGeometry.h"
#include "Geometry/CeilingGeometry.h"

#include "CeilingData.h"

#include <QJsonObject>
#include <QJsonDocument>

#include <iostream>  
#include <iomanip>  
#include <fstream>  

DesignDataWrapper* DesignDataWrapper::instance = 0;

DesignDataWrapper::DesignDataWrapper(){
  design_data_ = new DesignData();
   
  hot_region_ = new HotRegionGeometry(QPointF(100.0, 100.0), 50, 50);
  current_selected_geometry_ = NULL;
  design_data_id_ = 0;
}

void DesignDataWrapper::Draw(QPainter* painter){
  hot_region_->Draw(painter);
  for (int i = 0; i < auxiliary_lines_.size(); i++) {    
    auxiliary_lines_[i].Draw(painter);
  }
  for(int i=0;i<wall_geometrys_.size();i++){
    wall_geometrys_[i].Draw(painter);
  }

  for (int i = 0; i < inner_wall_geometrys_.size(); i++) {
    inner_wall_geometrys_[i]->Draw(painter);
  }

  for (int i = 0; i < model_geometrys_.size(); i++) {
    model_geometrys_[i].Draw(painter);
  }

  for (int i = 0; i < ceiling_geometrys_.size(); i++) {
    ceiling_geometrys_[i].Draw(painter);
  }

  if (current_selected_geometry_ != NULL ) {
    BaseGeometryData* geometry_data = current_selected_geometry_->data();
    if (geometry_data == NULL) {
      current_selected_geometry_->Draw(painter);
    }
    else if(geometry_data->is_tmp_data()){
      current_selected_geometry_->Draw(painter);
    }
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
  BaseGeometryData* tmp_data = NULL;
  if (current_selected_geometry_ != NULL) {
    tmp_data = current_selected_geometry_->data();
  }
  wall_geometrys_ = design_data_->ComputeWallGeometrys();
  if (tmp_data != NULL) {
    for(int i=0;i<wall_geometrys_.size();i++){
      if (tmp_data == wall_geometrys_[i].data()) {
        current_selected_geometry_ = (&wall_geometrys_[i]);
        break;
      }
        
    }
  }
  
  for (int i = 0; i < inner_wall_geometrys_.size(); i++) {
    delete inner_wall_geometrys_[i];
  }
  inner_wall_geometrys_.clear();
  inner_wall_geometrys_ = design_data_->GetInnerWallGeometry();
  if (tmp_data != NULL) {
    for (int i = 0; i < inner_wall_geometrys_.size(); i++) {
      if (inner_wall_geometrys_[i]->data() == tmp_data) {
        current_selected_geometry_ = inner_wall_geometrys_[i];
        break;
      }
    }
  }
  
  model_geometrys_ = design_data_->GetModelGeometry();
  if (tmp_data != NULL) {
    for(int i=0;i<model_geometrys_.size();i++){
      if (model_geometrys_[i].data() == tmp_data) {
        current_selected_geometry_ = (&model_geometrys_[i]);
        break;
      }
    }
  }

  ceiling_geometrys_ = design_data_->GetCeilingGeometry();
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

void DesignDataWrapper::set_current_selected_geometry(BaseGeometry* geometry) {
  if (current_selected_geometry_ != NULL && current_selected_geometry_->data()->is_tmp_data()) {
    delete_current_selected_geometry();
  }  
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
    case GEOMETRY_MODEL:
      insert_model_data((ModelData*)current_selected_geometry_->data());
      break;
    case GEOMETRY_CEILING:
      insert_ceiling_data((CeilingGeometry*)current_selected_geometry_);
    default:
      break;
  }
}

void DesignDataWrapper::insert_ceiling_data(CeilingGeometry* geometry) {
  if (geometry == NULL)
    return;
  QPointF position = geometry->position();
  RoomData* room_data = design_data_->FindRoomWithPosition(position);
  if (room_data != NULL) {
    BaseCeilingData* ceiling_data = (BaseCeilingData*)geometry->data();
    ceiling_data->set_room_name(room_data->name());
    ceiling_data->set_is_tmp_data(false);
    design_data_->AddCeiling(ceiling_data);
  }
}

void DesignDataWrapper::insert_opening_data(InnerWallGeometry* geometry) {
  //OPENING_TYPE opening_type = geometry->opening_type();
  WallData* wall_data = FindWallWithInnerWallGeometry(geometry);
  if (wall_data == NULL) {
    return;
  }
  //std::string opening_name = design_data_->GenerateOpeningName();
  OpeningData* data = (OpeningData*)(geometry->data());

  /*switch (opening_type) {
    case OPENING_SINGLE_DOOR:
      data = new OpeningData(*(SingleDoorGeometry*)geometry);
      break;
    case OPENING_MOVE_DOOR:
      data = new OpeningData(*((MoveDoorGeometry*)geometry));
      break;
    case OPENING_DOUBLE_DOOR:
      data = new OpeningData(*(DoubleDoorGeometry*)geometry);
      break;
    case OPENING_WINDOW:
      data = new OpeningData(*(WindowGeometry*)geometry);
      break;
    default:
      break;
  }*/

  

  if (data != NULL) {
    design_data_->AddOpening(data);
    wall_data->AddOpening(data->name());
  }  
}

WallData* DesignDataWrapper::FindWallWithInnerWallGeometry(InnerWallGeometry* geometry) {
  WallData* wall = NULL;
  QPointF position = geometry->position();
  WallGeometry wall_geometry;
  qreal distance;
  if (GetClosestWall(position, distance, wall_geometry)) {
    if (distance == 0) {
      wall = wall_geometry.wall_data();
    }
  }
  return wall;
}

void DesignDataWrapper::AddDesignDataId() {
  design_data_id_++;
}

int DesignDataWrapper::DesignDataId() {
  return design_data_id_;
}

std::string DesignDataWrapper::GetDesignData() {
  QJsonObject object = design_data_->ToJson();
  QJsonDocument doc(object);
  std::string result =  doc.toJson().toStdString();

  //std::ofstream outfile("d://b.txt");
  //outfile << result << std::endl;
  //outfile.close();
  return result;
}

void DesignDataWrapper::insert_model_data(ModelData* data) {
  design_data_->AddModel(data);
}

bool DesignDataWrapper::TrySelecteGeometry(const QPointF& point) {
  bool result = false;

  for (int i = 0; i < model_geometrys_.size(); i++) {
    if (model_geometrys_[i].IsPointIn(point)) {
      //current_selected_geometry_ = (BaseGeometry*)(&(model_geometrys_[i]));
      set_current_selected_geometry((BaseGeometry*)(&(model_geometrys_[i])));
      result = true;
      break;
    }
  }
  if (result) {
    return result;
  }

  for (int i = 0; i < inner_wall_geometrys_.size(); i++) {
    if (inner_wall_geometrys_[i]->IsPointIn(point)) {
      //current_selected_geometry_ = (BaseGeometry*)(inner_wall_geometrys_[i]);
      set_current_selected_geometry((BaseGeometry*)(inner_wall_geometrys_[i]));
      result = true;
      break;
    }
  }
  if (result) {
    return result;
  }

  for (int i = 0; i < wall_geometrys_.size(); i++) {
    if (wall_geometrys_[i].IsPointIn(point)) {      
      set_current_selected_geometry((BaseGeometry*)(&wall_geometrys_[i]));
      result = true;
      break;
    }
  }
  return result;
}