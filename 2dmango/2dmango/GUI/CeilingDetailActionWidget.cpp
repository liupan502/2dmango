#include "CeilingDetailActionWidget.h"
#include "Entity/DesignDataWrapper.h"
#include "Entity/CeilingData.h"
#include "Geometry/CeilingGeometry.h"
#include <QFile>

CeilingDetailActionWidget::CeilingDetailActionWidget(QWidget* parent) :BaseDetailActionWidget(parent) {
  ceiling_btn1_ = NULL;
}

CeilingDetailActionWidget::~CeilingDetailActionWidget() {
  if (ceiling_btn1_ != NULL) {
    delete ceiling_btn1_;
    ceiling_btn1_ = NULL;
  }
}

void CeilingDetailActionWidget::Init() {

  QPixmap ceiling_pixmap = QPixmap(100, 100);
  ceiling_pixmap.load("./icon/ceiling.png");
  QIcon ceiling_icon = QIcon(ceiling_pixmap);

  ceiling_btn1_ = new QPushButton(ceiling_icon,"",this);
  ceiling_btn1_->setIconSize(QSize(100, 100));
  ceiling_btn1_->setGeometry(30, 30, 100, 100);
  //ceiling_btn1_->
  //ceiling_btn1_->setText(QString::fromLocal8Bit("µõ¶¥1"));
  QFile style_sheet("./file/qss_file/detailaction.qss");
  if (style_sheet.open(QIODevice::ReadOnly)) {
    QString style_sheet_str = style_sheet.readAll();
    ceiling_btn1_->setStyleSheet(style_sheet_str);    
  }
  style_sheet.close();
  connect(ceiling_btn1_, SIGNAL(clicked()), this, SLOT(OnCeilingBtn1Clicked()));
}

void CeilingDetailActionWidget::OnCeilingBtn1Clicked() {
  DesignDataWrapper* instance = DesignDataWrapper::GetInstance();
  CrossSectionCeilingData* ceiling_data = CrossSectionCeilingData::CreateCeilingData1();
  CeilingGeometry* ceiling_geometry = new CeilingGeometry(ceiling_data);
  instance->set_current_selected_geometry(ceiling_geometry);  
}