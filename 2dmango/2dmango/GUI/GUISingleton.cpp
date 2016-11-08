#include "GUISingleton.h"
#include "actionnavgationwidget.h"
#include "DrawHouseDetailActionWidget.hpp"
#include "ModelSelectWidget.h"
#include "WorkSpaceWidget.hpp"

GUISingleton* GUISingleton::instance = NULL;

GUISingleton::GUISingleton() {
  set_model_selected_widget(NULL);
  set_draw_house_detail_action_widget(NULL);
  set_action_navigation_widget(NULL);
  set_work_space_widget(NULL);
}

GUISingleton* GUISingleton::Instance() {
  if (instance == NULL) {
    instance = new GUISingleton();
  }
  return instance;
}

void GUISingleton::set_action_navigation_widget(ActionNavigationWidget* widget) {
  action_navigation_widget_ = widget;
}

ActionNavigationWidget* GUISingleton::action_navigation_widget() {
  return action_navigation_widget_;
}

void GUISingleton::set_draw_house_detail_action_widget(DrawHouseDetailActionWidget* widget) {
  draw_house_detail_action_widget_ = widget;
}

DrawHouseDetailActionWidget* GUISingleton::draw_house_detail_action_widget() {
  return draw_house_detail_action_widget_;
}

void GUISingleton::set_model_selected_widget(ModelSelectWidget* widget) {
  model_selected_widget_ = widget;
}

ModelSelectWidget* GUISingleton::model_selected_widget() {
  return model_selected_widget_;
}


void GUISingleton::set_work_space_widget(WorkSpaceWidget* widget) {
  work_space_widget_ = widget;
}

WorkSpaceWidget* GUISingleton::work_space_widget() {
  return work_space_widget_;
}