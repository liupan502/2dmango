#include "DrawHouseDetailActionWidget.hpp"
#include "mango2d.h"
#include "WorkSpaceWidget.hpp"

DrawHouseDetailActionWidget::DrawHouseDetailActionWidget(QWidget * parent) : BaseDetailActionWidget(parent) {
	init();

}

DrawHouseDetailActionWidget::~DrawHouseDetailActionWidget() {
	
}

void DrawHouseDetailActionWidget::init() {
  draw_wall_btn_ = new QPushButton(this);
  draw_wall_btn_->setGeometry(30,30,100,50);
  draw_wall_btn_->setText(QString::fromLocal8Bit("画墙"));
  connect(draw_wall_btn_,SIGNAL(clicked()),this,SLOT(OnDrawWallBtnClicked()));
}

void DrawHouseDetailActionWidget::OnDrawWallBtnClicked(){
  Mango2d* parent = (Mango2d*)(parentWidget()->parentWidget()->parentWidget());
  WorkSpaceWidget* work_space_widget =  parent->work_space_widget();
  work_space_widget->BeginDrawWall();
}
