#include "DefaultActionAdapter.h"

DefaultActionAdapter::DefaultActionAdapter() :BaseActionAdapter() {
 
  left_mouse_down_ = false;
}

void DefaultActionAdapter::OnMouseLeave(QEvent* event) {
  left_mouse_down_ = false;
  
}

void DefaultActionAdapter::OnMouseRelease(QMouseEvent* event) {
  left_mouse_down_ = false;
  DesignDataWrapper* instance = DesignDataWrapper::GetInstance();
  BaseGeometry* current_selected_geometry = instance->current_selected_geometry();
  QPointF position = QPointF(event->pos());
  if (current_selected_geometry != NULL) {   
    instance->AddCurrentData();
    instance->AddGeometry(NULL);
    instance->UpdateGeometry();
    instance->AddDesignDataId();
  }
}

void DefaultActionAdapter::OnMousePress(QMouseEvent* event) {
  left_mouse_down_ = true;
  QPointF point = QPointF(event->pos());
  DesignDataWrapper* instance = DesignDataWrapper::GetInstance();
  bool is_selected_geometry = instance->TrySelecteGeometry(point);
  if (is_selected_geometry) {
    BaseGeometry* selected_geometry = instance->current_selected_geometry();
  }
}

void DefaultActionAdapter::OnMouseMove(QMouseEvent* event) {
  DesignDataWrapper* instance = DesignDataWrapper::GetInstance();
  BaseGeometry* current_selected_geometry = instance->current_selected_geometry();
  QPointF position = QPointF(event->pos());
  if (current_selected_geometry != NULL) {
    current_selected_geometry->MoveTo(position);
  }
}