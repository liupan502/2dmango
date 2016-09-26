#include "mango2d.h"
#include "GUI/actionnavgationwidget.h"


Mango2d::Mango2d(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this); 
  action_navi_widget_ = new ActionNavigationWidget(centralWidget());  
  work_space_widget_ = new WorkSpaceWidget(centralWidget());
  work_space_widget_->SwitchWorkMode(BASE_HOUSE_WORK_MODE);
}

Mango2d::~Mango2d()
{
  
}

ActionNavigationWidget* Mango2d::action_navigation_widget(){
  return action_navi_widget_;
}

WorkSpaceWidget* Mango2d::work_space_widget(){
  return work_space_widget_;
}