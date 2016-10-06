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

  window_btn_ = new QPushButton(this);
  window_btn_->setGeometry(30, 160, 100, 50);
  window_btn_->setText(QString::fromLocal8Bit("窗"));

  single_door_btn_ = new QPushButton(this);
  single_door_btn_->setGeometry(30, 290, 100, 50);
  single_door_btn_->setText(QString::fromLocal8Bit("单开门"));

  double_door_btn_ = new QPushButton(this);
  double_door_btn_->setGeometry(30, 420, 100, 50);
  double_door_btn_->setText(QString::fromLocal8Bit("双开门"));

  move_door_btn_ = new QPushButton(this);
  move_door_btn_->setGeometry(30, 550, 100, 50);
  move_door_btn_->setText(QString::fromLocal8Bit("移门"));

}

void DrawHouseDetailActionWidget::OnDrawWallBtnClicked(){
  Mango2d* parent = (Mango2d*)(parentWidget()->parentWidget()->parentWidget());
  WorkSpaceWidget* work_space_widget =  parent->work_space_widget();
  work_space_widget->BeginDrawWall();
}
