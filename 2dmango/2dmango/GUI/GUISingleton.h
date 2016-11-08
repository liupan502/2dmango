#pragma once

#include <QObject>
class ActionNavigationWidget;
class BaseDetailActionWidget;
class DrawHouseDetailActionWidget;
class ModelSelectWidget;
class WorkSpaceWidget;


class GUISingleton :public QObject {
public:
  GUISingleton();
  static GUISingleton* Instance();

  void set_action_navigation_widget(ActionNavigationWidget* widget);
  ActionNavigationWidget* action_navigation_widget();

  void set_draw_house_detail_action_widget(DrawHouseDetailActionWidget* widget);
  DrawHouseDetailActionWidget* draw_house_detail_action_widget();

  void set_model_selected_widget(ModelSelectWidget* widget);
  ModelSelectWidget* model_selected_widget();

  void set_work_space_widget(WorkSpaceWidget* widget);
  WorkSpaceWidget* work_space_widget();
private:
  static GUISingleton* instance;

  ActionNavigationWidget* action_navigation_widget_;
  DrawHouseDetailActionWidget* draw_house_detail_action_widget_;
  ModelSelectWidget* model_selected_widget_;
  WorkSpaceWidget* work_space_widget_;
};
