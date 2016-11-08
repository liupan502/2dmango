#include "actionnavgationwidget.h"
#include "GUI/ModelSelectItemDelegate.h"
#include "GUI/ModelSelectItemModel.h"
#include "GUISingleton.h"
#include <QFile>

ActionNavigationWidget::ActionNavigationWidget(QWidget * parent) : QWidget(parent) {
  detail_action_widget_ = NULL;
  
  Init();
}

ActionNavigationWidget::~ActionNavigationWidget() {
	
}

void ActionNavigationWidget::Init() {
  setGeometry(0,50,300,600);
  setAutoFillBackground(true);
  QPalette palette;
  palette.setColor(QPalette::Background, QColor(0, 255, 255));
  setPalette(palette);
  setWindowFlags(Qt::FramelessWindowHint);

  GUISingleton* gui_instance = GUISingleton::Instance();

  // 初始化“画户型”按钮
  base_draw_house_btn_  = new QPushButton(this);
  base_draw_house_btn_->setGeometry(0,0,100,50);
  base_draw_house_btn_->setText(QString::fromLocal8Bit("画户型")); 
  QFile style_sheet(":/file/qss_file/common.qss");
  if (style_sheet.open(QIODevice::ReadOnly)) {
    QString style_sheet_str = style_sheet.readAll();
    base_draw_house_btn_->setStyleSheet(style_sheet_str);
  }
  connect(base_draw_house_btn_, SIGNAL(clicked()), this, SLOT(OnDrawHouseClicked()));
  draw_house_detail_action_widget_ = new DrawHouseDetailActionWidget(this);
  draw_house_detail_action_widget_->setVisible(false);
  gui_instance->set_draw_house_detail_action_widget(draw_house_detail_action_widget_);
    // model select
  select_model_btn_ = new QPushButton(this);
  select_model_btn_->setGeometry(0, 50, 100, 50);
  select_model_btn_->setText(QString::fromLocal8Bit("挑家具"));
  if (style_sheet.open(QIODevice::ReadOnly)) {
    QString style_sheet_str = style_sheet.readAll();
    select_model_btn_->setStyleSheet(style_sheet_str);
  }
  connect(select_model_btn_, SIGNAL(clicked()), this, SLOT(OnSelectModelClicked()));
  model_select_widget_ = new ModelSelectWidget(this);
  model_select_widget_->Init(std::map<std::string, std::string>());
  model_select_widget_->setVisible(false);
  gui_instance->set_model_selected_widget(model_select_widget_);
  
  
  
  set_detail_action_widget(draw_house_detail_action_widget_);
  action_type_ = DRAW_WALL;
}

void ActionNavigationWidget::OnDrawHouseClicked(){
  if(action_type_ == DRAW_WALL)
    return;
  action_type_ = DRAW_WALL;
  set_detail_action_widget(draw_house_detail_action_widget_);
}

void ActionNavigationWidget::OnSelectModelClicked() {
  if (action_type_ == SELECT_MODEL)
    return;
  action_type_ = SELECT_MODEL;
  set_detail_action_widget(model_select_widget_);
}

void ActionNavigationWidget::set_detail_action_widget(BaseDetailActionWidget* widget) {
  if (widget == NULL)
    return;
  if (detail_action_widget_ != NULL) {
    detail_action_widget_->setVisible(false);
  }
  detail_action_widget_ = widget;
  detail_action_widget_->setVisible(true);
}
