#include "DefaultActionAdapter.h"
#include "GUI\GUISingleton.h"
#include "GUI\ItemPropertyWidget.h"
DefaultActionAdapter::DefaultActionAdapter() :BaseActionAdapter() {
 
  left_mouse_down_ = false;
}

void DefaultActionAdapter::OnMouseLeave(QEvent* event) {
  //left_mouse_down_ = false;
  BaseActionAdapter::OnMouseLeave(event);
}

void DefaultActionAdapter::OnMouseRelease(QMouseEvent* event) {
  //left_mouse_down_ = false;
  DesignDataWrapper* instance = DesignDataWrapper::GetInstance();
  BaseGeometry* current_selected_geometry = instance->current_selected_geometry();
  QPointF position = QPointF(event->pos());

  // 重新设定当前选中物体相关信息
  if (current_selected_geometry != NULL && move_status_ != NO_MOVE) {

    // 如果是新增数据，将数据添加到设计数据中
    if (current_selected_geometry->data()->is_tmp_data()) {
      instance->AddCurrentData();
    }

    // 当前选中物体置为空
    instance->set_current_selected_geometry(NULL);
    instance->UpdateGeometry();

    // 刷新设计数据
    instance->AddDesignDataId();
  }
  // 检查是否有数据被选中
  else {
    bool is_selected_geometry = instance->TrySelecteGeometry(position);
    if (!is_selected_geometry) {
      instance->set_current_selected_geometry(NULL);      
    }
    else {
      GUISingleton::Instance()->item_property_widget()->
        SetGetmetryData(instance->current_selected_geometry()->data());
    }
  }


  BaseActionAdapter::OnMouseRelease(event);
}

void DefaultActionAdapter::OnMousePress(QMouseEvent* event) {
  //left_mouse_down_ = true;
  /*QPointF point = QPointF(event->pos());
  DesignDataWrapper* instance = DesignDataWrapper::GetInstance();
  bool is_selected_geometry = instance->TrySelecteGeometry(point);
  if (is_selected_geometry) {
    BaseGeometry* selected_geometry = instance->current_selected_geometry();
  }*/

  BaseActionAdapter::OnMousePress(event);
}

void DefaultActionAdapter::OnMouseMove(QMouseEvent* event) {
  DesignDataWrapper* instance = DesignDataWrapper::GetInstance();
  BaseGeometry* current_selected_geometry = instance->current_selected_geometry();
  QPointF position = QPointF(event->pos());
  if (current_selected_geometry != NULL ) {
    current_selected_geometry->MoveTo(position);
  }

  BaseActionAdapter::OnMouseMove(event);
}