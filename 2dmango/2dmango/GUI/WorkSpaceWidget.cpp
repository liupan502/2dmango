#include "WorkSpaceWidget.hpp"
#include <QPainter>
#include "Entity/DesignDataWrapper.h"


WorkSpaceWidget::WorkSpaceWidget(QWidget * parent) : QWidget(parent) {
	init();
  setMouseTracking(true);
  mouse_adapter_ = new BaseActionAdapter();
  default_action_adapter_ = new DefaultActionAdapter();
  mouse_adapter_ = default_action_adapter_;
  draw_wall_mouse_adapter_ = NULL;
  work_mode_ = NONE_WORK_MODE;
  int a = 0;
}

WorkSpaceWidget::~WorkSpaceWidget() {
	
}

void WorkSpaceWidget::init() {
  setGeometry(300,50,980,670);
  setAutoFillBackground(true);
  QPalette palette;
  palette.setColor(QPalette::Background, QColor(255, 255, 255));
  setPalette(palette);
}

void WorkSpaceWidget::paintEvent(QPaintEvent* event){
  QPainter* paint = new QPainter();
  paint->begin(this);  
  DesignDataWrapper::GetInstance()->Draw(paint);
  paint->end();
  //repaint(rect());
}

void WorkSpaceWidget::mouseMoveEvent(QMouseEvent* event){
  if(mouse_adapter_ == NULL)
    return;
  mouse_adapter_->OnMouseMove(event);
  repaint(rect());
}

void WorkSpaceWidget::mousePressEvent(QMouseEvent* event){
  if(mouse_adapter_ == NULL)
    return;  
  mouse_adapter_->OnMousePress(event);
}

void WorkSpaceWidget::mouseReleaseEvent(QMouseEvent* event){
  if(mouse_adapter_ == NULL)
    return;
  mouse_adapter_->OnMouseRelease(event);
}

void WorkSpaceWidget::leaveEvent(QEvent* event){
  if(mouse_adapter_ == NULL)
    return;
  mouse_adapter_->OnMouseLeave(event);
}

void WorkSpaceWidget::SwitchWorkMode(WORK_MODE mode){
  work_mode_ = mode;
}

void WorkSpaceWidget::BeginDrawWall(){
  if(work_mode_ != BASE_HOUSE_WORK_MODE)
    return;
  if(draw_wall_mouse_adapter_ == NULL){
    draw_wall_mouse_adapter_ = new DrawWallActionAdapter();
    connect(draw_wall_mouse_adapter_, SIGNAL(EndDrawWall()), this, SLOT(EndDrawWall()));    
  }
  mouse_adapter_ = draw_wall_mouse_adapter_;  
  
} 

void WorkSpaceWidget::EndDrawWall() {
  mouse_adapter_ = default_action_adapter_;
}
