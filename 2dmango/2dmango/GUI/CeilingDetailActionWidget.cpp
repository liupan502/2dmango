#include "CeilingDetailActionWidget.h"
#include "Entity/DesignDataWrapper.h"
#include "Entity/CeilingData.h"
#include "Geometry/CeilingGeometry.h"

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
  ceiling_btn1_ = new QPushButton(this);
  ceiling_btn1_->setGeometry(30, 30, 100, 50);
  ceiling_btn1_->setText(QString::fromLocal8Bit("µõ¶¥1"));
  connect(ceiling_btn1_, SIGNAL(clicked()), this, SLOT(OnCeilingBtn1Clicked()));
}

void CeilingDetailActionWidget::OnCeilingBtn1Clicked() {
  DesignDataWrapper* instance = DesignDataWrapper::GetInstance();
  CrossSectionCeilingData* ceiling_data = CrossSectionCeilingData::CreateCeilingData1();
  CeilingGeometry* ceiling_geometry = new CeilingGeometry(ceiling_data);
  instance->set_current_selected_geometry(ceiling_geometry);  
}