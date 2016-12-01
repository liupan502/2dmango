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

  // �����趨��ǰѡ�����������Ϣ
  if (current_selected_geometry != NULL && move_status_ != NO_MOVE) {

    // ������������ݣ���������ӵ����������
    if (current_selected_geometry->data()->is_tmp_data()) {
      instance->AddCurrentData();
    }

    // ��ǰѡ��������Ϊ��
    instance->set_current_selected_geometry(NULL);
    instance->UpdateGeometry();

    // ˢ���������
    instance->AddDesignDataId();
  }
  // ����Ƿ������ݱ�ѡ��
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