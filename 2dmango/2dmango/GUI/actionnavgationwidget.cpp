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
  palette.setColor(QPalette::Background, QColor("#ededed"));
  setPalette(palette);
  setWindowFlags(Qt::FramelessWindowHint);

  GUISingleton* gui_instance = GUISingleton::Instance();

  // 初始化“画户型”按钮
  //QPixmap pixmap = NULL;
  QPixmap draw_house_pixmap = QPixmap(80, 80);
  draw_house_pixmap.load("./icon/drawhouse.png");
  QIcon draw_house_icon = QIcon(draw_house_pixmap);
  base_draw_house_btn_  = new QPushButton(draw_house_icon,"",this);
  base_draw_house_btn_->setIconSize(QSize(80.0, 80.0));
  base_draw_house_btn_->setGeometry(10,20,80,80);
  //base_draw_house_btn_->setText(QString::fromLocal8Bit("画户型"));   
  connect(base_draw_house_btn_, SIGNAL(clicked()), this, SLOT(OnDrawHouseClicked()));
  draw_house_detail_action_widget_ = new DrawHouseDetailActionWidget(this);
  draw_house_detail_action_widget_->setVisible(false);
  gui_instance->set_draw_house_detail_action_widget(draw_house_detail_action_widget_);
    // model select

  QPixmap select_model_pixmap = QPixmap(80, 80);
  select_model_pixmap.load("./icon/selectmodel.png");
  QIcon select_model_icon = QIcon(select_model_pixmap);
  select_model_btn_ = new QPushButton(select_model_icon, "", this);
  select_model_btn_->setGeometry(10, 100, 80, 80);
  select_model_btn_->setIconSize(QSize(80.0, 80.0));
  //select_model_btn_->setText(QString::fromLocal8Bit("挑家具"));
  
  connect(select_model_btn_, SIGNAL(clicked()), this, SLOT(OnSelectModelClicked()));
  model_select_widget_ = new ModelSelectWidget(this);
  model_select_widget_->Init(std::map<std::string, std::string>());
  model_select_widget_->setVisible(false);
  gui_instance->set_model_selected_widget(model_select_widget_);
  

  QPixmap ceiling_pixmap = QPixmap(80, 80);
  ceiling_pixmap.load("./icon/ceiling.png");
  QIcon ceiling_icon = QIcon(ceiling_pixmap);
  ceiling_btn_ = new QPushButton(ceiling_icon, "", this);
  ceiling_btn_->setIconSize(QSize(80.0, 80.0));
  ceiling_btn_->setGeometry(10, 180, 80, 80);
  //ceiling_btn_->setText(QString::fromLocal8Bit("吊顶"));
  connect(ceiling_btn_, SIGNAL(clicked()), this, SLOT(OnCeilingClicked()));
  ceiling_detail_action_widget_ = new CeilingDetailActionWidget(this);
  ceiling_detail_action_widget_->Init();
  ceiling_detail_action_widget_->setVisible(false);


  //QFile style_sheet(":/file/qss_file/common.qss");
  QFile style_sheet("./file/qss_file/common.qss");
  if (style_sheet.open(QIODevice::ReadOnly)) {
    QString style_sheet_str = style_sheet.readAll();
    base_draw_house_btn_->setStyleSheet(style_sheet_str);
    select_model_btn_->setStyleSheet(style_sheet_str);
    ceiling_btn_->setStyleSheet(style_sheet_str);
  }
  style_sheet.close();
  
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

void ActionNavigationWidget::OnCeilingClicked() {
  if (action_type_ == CEILING)
    return;
  action_type_ = CEILING;
  set_detail_action_widget(ceiling_detail_action_widget_);
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
