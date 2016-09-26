#include "actionnavgationwidget.h"
#include <QFile>

ActionNavigationWidget::ActionNavigationWidget(QWidget * parent) : QWidget(parent) {
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
  
  detail_action_widget_ = draw_house_detail_action_widget_;
  action_type_ = DRAW_WALL;
}

void ActionNavigationWidget::OnDrawHouseClicked(){
  if(action_type_ == DRAW_WALL)
    return;
  action_type_ = DRAW_WALL;
  detail_action_widget_ = draw_house_detail_action_widget_;
}
