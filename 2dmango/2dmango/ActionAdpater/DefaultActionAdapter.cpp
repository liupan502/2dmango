#include "DefaultActionAdapter.h"

DefaultActionAdapter::DefaultActionAdapter() :BaseActionAdapter() {
  current_selected_geometry_ = NULL;
  left_mouse_down_ = false;
}

void DefaultActionAdapter::OnMouseLeave(QEvent* event) {
  left_mouse_down_ = false;
  
}

void DefaultActionAdapter::OnMouseRelease(QMouseEvent* event) {
  left_mouse_down_ = false;
  if (current_selected_geometry_ == NULL) {

  }
  else {

  }
}

void DefaultActionAdapter::OnMousePress(QMouseEvent* event) {
  left_mouse_down_ = true;
}

void DefaultActionAdapter::OnMouseMove(QMouseEvent* event) {

}