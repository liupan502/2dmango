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
  
}

void DefaultActionAdapter::OnMouseMove(QMouseEvent* event) {
  DesignDataWrapper* instance = DesignDataWrapper::GetInstance();
  BaseGeometry* current_selected_geometry = instance->current_selected_geometry();
  QPointF position = QPointF(event->pos());
  if (current_selected_geometry != NULL) {
    current_selected_geometry->MoveTo(position);
  }
}