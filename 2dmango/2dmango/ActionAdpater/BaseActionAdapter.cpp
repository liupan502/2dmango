#include "BaseActionAdapter.h"

BaseActionAdapter::BaseActionAdapter() {
  is_left_mouse_down_ = false;
  move_status_ = NO_MOVE;
}

void BaseActionAdapter::OnMouseMove(QMouseEvent* event){
  move_status_ = is_left_mouse_down_ ? DOWN_MOVE : UP_MOVE;
}

void BaseActionAdapter::OnMousePress(QMouseEvent* event){
  is_left_mouse_down_ = true;
  //move_status_ = NO_MOVE;
}

void BaseActionAdapter::OnMouseRelease(QMouseEvent* event){
  is_left_mouse_down_ = false;
  move_status_ = NO_MOVE;
}

void BaseActionAdapter::OnMouseLeave(QEvent* event) {
  is_left_mouse_down_ = false;
  move_status_ = NO_MOVE;
}