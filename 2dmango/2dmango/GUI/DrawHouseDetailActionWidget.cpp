#include "DrawHouseDetailActionWidget.hpp"
#include "mango2d.h"
#include "WorkSpaceWidget.hpp"
#include "Entity/DesignDataWrapper.h"
#include "Entity/OpeningData.h"
#include "Geometry/SingleDoorGeometry.h"
#include "Geometry/DoubleDoorGeometry.h"
#include "Geometry/MoveDoorGeometry.h"
#include "Geometry/WindowGeometry.h"
#include "const.h"

DrawHouseDetailActionWidget::DrawHouseDetailActionWidget(QWidget * parent) : BaseDetailActionWidget(parent) {
	init();

}

DrawHouseDetailActionWidget::~DrawHouseDetailActionWidget() {
	
}

void DrawHouseDetailActionWidget::init() {

  QPixmap draw_house_pixmap = QPixmap(80, 80);
  draw_house_pixmap.load("./icon/drawhouse.png");
  QIcon draw_house_icon = QIcon(draw_house_pixmap);
  draw_wall_btn_ = new QPushButton(draw_house_pixmap,"",this);
  draw_wall_btn_->setIconSize(QSize(80, 80));
  draw_wall_btn_->setGeometry(20,20,80,80);
  //draw_wall_btn_->setText(QString::fromLocal8Bit("画墙"));
  connect(draw_wall_btn_,SIGNAL(clicked()),this,SLOT(OnDrawWallBtnClicked()));


  QPixmap window_pixmap = QPixmap(80, 80);
  window_pixmap.load("./icon/window.png");
  QIcon window_icon = QIcon(window_pixmap);
  window_btn_ = new QPushButton(window_icon,"",this);
  window_btn_->setGeometry(100, 20, 80, 80);
  window_btn_->setIconSize(QSize(80, 80));
  //window_btn_->setText(QString::fromLocal8Bit("窗"));
  connect(window_btn_, SIGNAL(clicked()), this, SLOT(OnWindowBtnClicked()));

  QPixmap single_door_pixmap = QPixmap(80, 80);
  single_door_pixmap.load("./icon/singledoor.png");
  QIcon single_door_icon = QIcon(single_door_pixmap);
  single_door_btn_ = new QPushButton(single_door_icon,"",this);
  single_door_btn_->setIconSize(QSize(80, 80));
  single_door_btn_->setGeometry(20, 100, 80, 80);
  //single_door_btn_->setText(QString::fromLocal8Bit("单开门"));
  connect(single_door_btn_, SIGNAL(clicked()), this, SLOT(OnSingleDoorBtnClicked()));

  /*double_door_btn_ = new QPushButton(this);
  double_door_btn_->setGeometry(30, 420, 100, 50);
  double_door_btn_->setText(QString::fromLocal8Bit("双开门"));
  connect(double_door_btn_, SIGNAL(clicked()), this, SLOT(OnDoubleDoorBtnClicked()));

  move_door_btn_ = new QPushButton(this);
  move_door_btn_->setGeometry(30, 550, 100, 50);
  move_door_btn_->setText(QString::fromLocal8Bit("移门"));
  connect(move_door_btn_, SIGNAL(clicked()), this, SLOT(OnMoveDoorBtnClicked()));
  */
  QFile style_sheet("./file/qss_file/detailaction.qss");
  if (style_sheet.open(QIODevice::ReadOnly)) {
    QString style_sheet_str = style_sheet.readAll();
    draw_wall_btn_->setStyleSheet(style_sheet_str);
    window_btn_->setStyleSheet(style_sheet_str);
    single_door_btn_->setStyleSheet(style_sheet_str);
  }
  style_sheet.close();

}

void DrawHouseDetailActionWidget::OnDrawWallBtnClicked(){
  Mango2d* parent = (Mango2d*)(parentWidget()->parentWidget()->parentWidget());
  WorkSpaceWidget* work_space_widget =  parent->work_space_widget();
  work_space_widget->BeginDrawWall();
}

void DrawHouseDetailActionWidget::OnDoubleDoorBtnClicked() {
  DesignDataWrapper* instance = DesignDataWrapper::GetInstance();
  OpeningData* opening_data = new OpeningData(OPENING_DOUBLE_DOOR);
  opening_data->set_width(DEFAULT_WALL_WIDTH);
  opening_data->set_length(2 * DEFAULT_SINGLE_DOOR_LENGTH);
  opening_data->set_height(180);
  DoubleDoorGeometry* double_door_geometry = new DoubleDoorGeometry(opening_data);
  instance->set_current_selected_geometry(double_door_geometry);
}

void DrawHouseDetailActionWidget::OnMoveDoorBtnClicked() {
  DesignDataWrapper* instance = DesignDataWrapper::GetInstance();
  OpeningData* opening_data = new OpeningData(OPENING_MOVE_DOOR);
  opening_data->set_width(DEFAULT_WALL_WIDTH);
  opening_data->set_length(1.5 * DEFAULT_SINGLE_DOOR_LENGTH);
  opening_data->set_height(180);
  MoveDoorGeometry* move_door_geometry = new MoveDoorGeometry(opening_data);
  instance->set_current_selected_geometry(move_door_geometry);
}

void DrawHouseDetailActionWidget::OnSingleDoorBtnClicked() {
  DesignDataWrapper* instance = DesignDataWrapper::GetInstance();
  OpeningData* opening_data = new OpeningData(OPENING_SINGLE_DOOR);
  opening_data->set_width(DEFAULT_WALL_WIDTH);
  //opening_data->set_length(DEFAULT_SINGLE_DOOR_LENGTH);
  opening_data->set_length(102);
  opening_data->set_height(210);
  SingleDoorGeometry* single_door_geometry = new SingleDoorGeometry(opening_data);
  instance->set_current_selected_geometry(single_door_geometry);
}

void DrawHouseDetailActionWidget::OnWindowBtnClicked() {
  DesignDataWrapper* instance = DesignDataWrapper::GetInstance();
  OpeningData* opening_data = new OpeningData(OPENING_WINDOW);
  opening_data->set_width(DEFAULT_WALL_WIDTH);
  //opening_data->set_length(DEFAULT_SINGLE_DOOR_LENGTH);
  opening_data->set_length(179);
  opening_data->set_height(210);
  
  WindowGeometry* window_geometry = new WindowGeometry(opening_data);
  instance->set_current_selected_geometry(window_geometry);
}
