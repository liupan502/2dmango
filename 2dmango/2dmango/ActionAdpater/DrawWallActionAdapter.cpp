#include "DrawWallActionAdapter.h"
#include "Entity/DesignDataWrapper.h"

#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

const int draw_none = 0;
const int draw_ready = 1;
const int draw_initilizing = 2;
const int draw_drawing = 3;

DrawWallActionAdapter::DrawWallActionAdapter(){
  previous_corner_ = NULL;
  current_corner_ = NULL;

  previous_point_ = QPoint();
  current_point_ = QPoint();

  left_mouse_down_ = false;
  bdrawing_ = false;
  is_fixed_ = false;
  is_current_room_completed_ = false;
  tmp_wall_ = NULL;
  draw_status_ = draw_ready;

}

void DrawWallActionAdapter::OnMouseMove(QMouseEvent* event){
  switch (draw_status_) {
    case draw_ready:
      ready_mouse_move(event);
      break;
    case draw_initilizing:
      initilizing_mouse_move(event);
      break;
    case draw_drawing:
      drawing_mouse_move(event);
      break;
    default:
     break;
  }
}

void DrawWallActionAdapter::OnMousePress(QMouseEvent* event){
  if(event->button() == Qt::LeftButton){
    left_mouse_button_press(event);
  }
}

void DrawWallActionAdapter::OnMouseRelease(QMouseEvent* event){
  if(event->button() == Qt::LeftButton){
    left_mouse_button_release(event);
  }
  else if(event->button() == Qt::RightButton){
    right_mouse_button_release(event);
  }
}

void DrawWallActionAdapter::left_mouse_button_press(QMouseEvent* event){
  switch (draw_status_) {
    case draw_ready:
      ready_left_mouse_press(event);
      break;
    case draw_initilizing:
      initilizing_left_mouse_press(event);
      break;
    case draw_drawing:
      drawing_left_mouse_press(event);
      break;
    default:
      break;
  }
}

void DrawWallActionAdapter::left_mouse_button_release(QMouseEvent* event){
  switch (draw_status_) {
    case draw_ready:
      ready_left_mouse_release(event);
      break;
    case draw_initilizing:
      initilizing_left_mouse_release(event);
      break;
    case draw_drawing:
      drawing_left_mouse_release(event);
      break;
    default:
      break;
  }
}

void DrawWallActionAdapter::right_mouse_button_release(QMouseEvent* event){
  bdrawing_ = false;
  tmp_wall_ = NULL;
  DesignDataWrapper* ptr = DesignDataWrapper::GetInstance();
  previous_corner_ = NULL;
  current_corner_ = NULL;
  draw_status_ = draw_ready;
}

void DrawWallActionAdapter::ready_mouse_move(QMouseEvent* event) {
  //OutputDebugString(TEXT("在调试器里输出的类容\n"));
  QPointF current_point = QPointF(event->pos());  
  DesignDataWrapper* instance = DesignDataWrapper::GetInstance();
  QPointF point;
  if (instance->FindStartPoint(current_point, point)) {
    start_point_ = point;
    instance->HotRegionMoveTo(point);
    instance->ShowHotRegion(true);
    //OutputDebugString(TEXT("find start point\n"));
  }
  else {
    //OutputDebugString(TEXT("not find start point\n"));
  }
}

void DrawWallActionAdapter::initilizing_mouse_move(QMouseEvent* event) {  
  QPoint pos = event->pos();
  if (tmp_wall_ != NULL) {    
   
    DesignDataWrapper* instance = DesignDataWrapper::GetInstance();
    if (instance->IsPointInHotRegion(pos)) {
      tmp_wall_->set_end_corner_position(QPointF(pos));
      OutputDebugString(TEXT("initilizing_mouse_move inside region\n"));
    }
    else {
      OutputDebugString(TEXT("initilizing_mouse_move outside region\n"));
      draw_status_ = draw_drawing;
      QPointF start_point = tmp_wall_->start_corner_position();
      qreal offset_x = pos.x() - start_point.x();
      qreal offset_y = pos.y() - start_point.y();
      if (abs(offset_x) > abs(offset_y)) {
        pos= QPoint(pos.x(),start_point.y());
      }
      else {
        pos = QPoint(start_point.x(),pos.y());
      }
      
      tmp_wall_->set_end_corner_position(QPointF(pos));
      instance->HotRegionMoveTo(pos);
    }
  }
  else {
    tmp_wall_ = DesignDataWrapper::GetInstance()->AddWall();
	  tmp_wall_->set_status(DRAWING_WALL_DATA);
    if (previous_corner_ == NULL) {
      //tmp_wall_->set_own_start_corner_data(true);
    }
    previous_corner_ = current_corner_;
    previous_point_ = current_point_;
    current_corner_ = DesignDataWrapper::GetInstance()->AddCorner();
    current_point_ = pos;
    tmp_wall_->set_start_corner(previous_corner_);
    
    tmp_wall_->set_start_corner_position(previous_point_);
    
    tmp_wall_->set_end_corner(current_corner_);
    //tmp_wall_->set_end_corner_name(current_corner_->name());
    tmp_wall_->set_end_corner_position(QPointF(pos));
    //tmp_wall_->set_own_end_corner_data(true);
    //tmp_wall_->set_end_corner(current_corner_);
  }
}

void DrawWallActionAdapter::drawing_mouse_move(QMouseEvent* event) {  
  QPointF pos = event->pos();
  
  if (tmp_wall_ != NULL) {    
    DesignDataWrapper* instance = DesignDataWrapper::GetInstance();
    if (instance->IsPointInHotRegion(QPointF(pos))) {   
      instance->ClearAuxiliaryLines();
      pos = compute_right_position(tmp_wall_,pos);
      tmp_wall_->set_end_corner_position(pos);
      std::vector<QPointF> points;
      bool is_fixed = false;
      if (!is_first_room_) {
        int a = 0;
      }
      if (instance->FindConnectedPoints(pos, tmp_wall_->name(), points)) {
        
        pos = compute_connected_position(tmp_wall_, points[0]);
        
        instance->AddAuxiliaryLine(pos,points[0]);        
        tmp_wall_->set_end_corner_position(pos);   
        is_fixed = true;		
      }
      points.clear();
      std::vector<CornerData*> corners;
      if (instance->FindAttachedCorner(pos, tmp_wall_->name(), corners)) {
        CornerData* corner = corners[0];
        QPointF end_point;
        if (instance->FindEndPoint(tmp_wall_, corner, pos, end_point)) {
          pos = end_point;
          tmp_wall_->set_end_corner(corner);
          tmp_wall_->set_end_corner_position(pos);          
          is_current_room_completed_ = true;
          draw_status_ = draw_ready;
        }
        
      }
      is_fixed_ = is_fixed;
      current_point_ = pos;      
      instance->HotRegionMoveTo(QPointF(pos));
      instance->UpdateGeometry();
    }
    else {
      return;
    }
  }  
}

void DrawWallActionAdapter::ready_left_mouse_press(QMouseEvent* event) {  
  DesignDataWrapper* instance = DesignDataWrapper::GetInstance();
  
  previous_corner_ = current_corner_;
  previous_point_ = current_point_;
  QPointF pos = start_point_.isNull()?event->pos(): start_point_; 
  
  if (current_corner_ == NULL) {
    if (!start_point_.isNull()) {
      int a = 0;
    }
    if (!instance->IsEmpty() && start_point_.isNull()) {
      return;
    }
    if (!start_point_.isNull()) {
      CornerData* tmp_corner = instance->FindCornerWithPosition(start_point_);
      if (tmp_corner != NULL) {
        current_corner_ = tmp_corner;
        is_first_room_ = false;
      }
    }
    if (current_corner_ == NULL) {
      current_corner_ = instance->AddCorner();
      is_first_room_ = true;
    }
    
    current_point_ = pos;
    instance->HotRegionMoveTo(event->pos());
    instance->ShowHotRegion(true);
    draw_status_ = draw_initilizing;
  }
  else if(instance->IsPointInHotRegion(pos)){    
	  if (!is_current_room_completed_) {
      if (!instance->IsEmpty() && start_point_.isNull()) {
        return;
      }
		  instance->HotRegionMoveTo(event->pos());
		  instance->ShowHotRegion(true);
      draw_status_ = draw_initilizing;
	  }
	  else {
      if (!is_first_room_) {
        int a = 0;
      }
		  instance->HotRegionMoveTo(event->pos());
		  instance->ShowHotRegion(false);
		  instance->UpdateRoomInfo();
		  instance->UpdateGeometry();
      current_corner_ = NULL;
      previous_corner_ = NULL;
      tmp_wall_ = NULL;
		  is_current_room_completed_ = false;
	  }
    
  }  

  start_point_ = QPointF();
}

void DrawWallActionAdapter::initilizing_left_mouse_press(QMouseEvent* event) {
  ;
}

void DrawWallActionAdapter::drawing_left_mouse_press(QMouseEvent* event) {
  QPointF pos = event->pos();
  DesignDataWrapper* instance = DesignDataWrapper::GetInstance();
  if (!instance->IsPointInHotRegion(pos)) {
    return;
  }
  draw_status_ = draw_initilizing;  
  if (!is_fixed_) {
    pos = compute_right_position(tmp_wall_, pos);
    current_point_ = pos;
  }  
  tmp_wall_->set_end_corner_position(current_point_);
  tmp_wall_ = NULL;
}

void DrawWallActionAdapter::ready_left_mouse_release(QMouseEvent* event) {
  
}

void DrawWallActionAdapter::initilizing_left_mouse_release(QMouseEvent* event) {    
}

void DrawWallActionAdapter::drawing_left_mouse_release(QMouseEvent* event) {
  ;
}

QPointF DrawWallActionAdapter::compute_right_position(WallData* wall, QPointF position) {
  QPointF start_point = wall->start_corner_position();
  QPointF end_point = wall->end_corner_position();
  qreal x = start_point.x() - end_point.x();
  qreal y = start_point.y() - end_point.y();
  if (abs(x) > abs(y)) {
    return QPoint(position.x(), end_point.y());
  }
  else {
    return QPoint(end_point.x(), position.y());
  }
}

QPointF DrawWallActionAdapter::compute_connected_position(WallData* wall, QPointF connectPoint) {
  QLineF wall_line = wall->WallLine();
  QVector2D perpendicular_vec = wall->WallPerpendicularVector();
  perpendicular_vec.normalize();
  qreal x = perpendicular_vec.x()*100 + connectPoint.x();
  qreal y = perpendicular_vec.y()*100 + connectPoint.y();
  QPointF another_point(x,y);
  QLineF perpendicular_line = QLineF(connectPoint,another_point);
  QPointF intersect_point;
  wall_line.intersect(perpendicular_line,&intersect_point);
  return intersect_point;
}

void DrawWallActionAdapter::current_room_complete(std::string corner_name) {
  
}

