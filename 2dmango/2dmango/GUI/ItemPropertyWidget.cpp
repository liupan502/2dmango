#include "ItemPropertyWidget.h"
#include <QPushButton>
#include <QLabel>
ItemPropertyWidget::ItemPropertyWidget(QWidget * parent ) : QWidget(parent) {
  init(parent);
}

ItemPropertyWidget::~ItemPropertyWidget() {

}

void ItemPropertyWidget::SetGetmetryData(BaseGeometryData* data) {
  if (detail_widget_ != NULL) {
    detail_widget_->set_data(data);
  }
}

void ItemPropertyWidget::init(QWidget * parent) {
  QSize parent_size = parent->size();
  setGeometry(1080, 50, 200, 200);  
  setAutoFillBackground(true);
  QPalette palette;
  palette.setColor(QPalette::Background, QColor(0, 0, 255));
  setPalette(palette);
  setWindowFlags(Qt::FramelessWindowHint);

  opening_detail_widget_ = new OpeningPropertyDetailWidget(this);
  model_detail_widget_ = new ModelPropertyDetailWidget(this);
  opening_detail_widget_->setVisible(false);
  model_detail_widget_->setVisible(false);

  detail_widget_ = opening_detail_widget_;
  detail_widget_->setVisible(true);
}

BaseItemPropertyDetailWidget::BaseItemPropertyDetailWidget(QWidget * parent ):QWidget(parent) {
  init();
}

BaseItemPropertyDetailWidget::~BaseItemPropertyDetailWidget(){
}

void BaseItemPropertyDetailWidget::init() {
  setGeometry(0, 0, 200, 200);
  setAutoFillBackground(true);
  QPalette palette;
  palette.setColor(QPalette::Background, QColor(255, 255, 0));
  setPalette(palette);
  setWindowFlags(Qt::FramelessWindowHint);
}

OpeningPropertyDetailWidget::OpeningPropertyDetailWidget(QWidget * parent ): BaseItemPropertyDetailWidget(parent){
  init();
  connect(spin_box_offset_z_, SIGNAL(valueChanged(int)), this, SLOT(OnOffsetZChanged(int)));
  connect(spin_box_length_, SIGNAL(valueChanged(int)), this, SLOT(OnOffsetLengthChanged(int)));
  connect(spin_box_width_, SIGNAL(valueChanged(int)), this, SLOT(OnOffsetWidthChanged(int)));
}

void OpeningPropertyDetailWidget::OnOffsetZChanged(int value) {
  if (!data_)
    return;
  QVector3D tmp_position = data_->position();
  tmp_position.setZ(value);
  data_->set_position(tmp_position);
}

void OpeningPropertyDetailWidget::OnLengthChanged(int value) {
  if (!data_)
    return;  
  data_->set_length(value);
}

void OpeningPropertyDetailWidget::OnWidthChanged(int value) {
  if (!data_)
    return;  
  data_->set_width(value);
}

OpeningPropertyDetailWidget::~OpeningPropertyDetailWidget() {

}

void OpeningPropertyDetailWidget::set_data(BaseGeometryData* data) {
  if (!data||data_->geometry_type() != GEOMETRY_OPENING)
    return;
  data_ = data;
  spin_box_offset_z_->setValue(data_->position().z());
  spin_box_length_->setValue(data_->length());
  spin_box_width_->setValue(data_->width());
}

void OpeningPropertyDetailWidget::UpdateContent(bool isViewToData) {

}

void OpeningPropertyDetailWidget::init() {
  QLabel* label_offset_z = new QLabel((QWidget*)this);
  label_offset_z->setGeometry(20, 20, 40, 60);
  label_offset_z->setText(QString("offset_Z"));

  spin_box_offset_z_ = new QSpinBox(this);
  spin_box_offset_z_->setGeometry(100, 35, 80, 30);
  spin_box_offset_z_->setRange(0, 200);

  QLabel* label_length = new QLabel((QWidget*)this);
  label_length->setGeometry(20, 80, 40, 60);
  label_length->setText(QString("length"));

  spin_box_length_ = new QSpinBox(this);
  spin_box_length_->setGeometry(100, 95, 80, 30);
  spin_box_length_->setRange(0, 360);

  QLabel* label_width = new QLabel((QWidget*)this);
  label_width->setGeometry(20, 140, 40, 60);
  label_width->setText(QString("length"));

  spin_box_width_ = new QSpinBox(this);
  spin_box_width_->setGeometry(100, 155, 80, 30);
  spin_box_width_->setRange(0, 360);
}

ModelPropertyDetailWidget::ModelPropertyDetailWidget(QWidget * parent ):BaseItemPropertyDetailWidget(parent) {
  init();
  connect(spin_box_offset_z_, SIGNAL(valueChanged(int)), this, SLOT(OnOffsetZChanged(int)));
  connect(spin_box_rotation_, SIGNAL(valueChanged(int)), this, SLOT(OnRotationChanged(int)));
}

ModelPropertyDetailWidget::~ModelPropertyDetailWidget() {

}

void ModelPropertyDetailWidget::set_data(BaseGeometryData* data) {
  if (!data||data->geometry_type() != GEOMETRY_MODEL)
    return;
  data_ = data;
  spin_box_offset_z_->setValue(data_->position().z());
  spin_box_rotation_->setValue(data_->rotation_z());
}

void ModelPropertyDetailWidget::UpdateContent(bool isViewToData) {

}

void ModelPropertyDetailWidget::init() {
  QLabel* label_offset_z = new QLabel((QWidget*)this);
  label_offset_z->setGeometry(20, 20, 60, 60);
  label_offset_z->setText(QString("offset_Z"));

  spin_box_offset_z_ = new QSpinBox(this);
  spin_box_offset_z_->setGeometry(100, 35, 80, 30);
  spin_box_offset_z_->setRange(0, 200);

  QLabel* label_rotation = new QLabel((QWidget*)this);
  label_rotation->setGeometry(20, 100, 60, 60);
  label_rotation->setText(QString("rotation"));

  spin_box_rotation_ = new QSpinBox(this);
  spin_box_rotation_->setGeometry(100, 115, 80, 30);
  spin_box_rotation_->setRange(0, 360);

}

void ModelPropertyDetailWidget::OnOffsetZChanged(int value) {
  if (!data_)
    return;
  QVector3D tmp_position = data_->position();
  tmp_position.setZ(value);
  data_->set_position(tmp_position);
}

void ModelPropertyDetailWidget::OnRotationChanged(int value) {
  if (data_)
    return;
  //float radian = M_2_PI*((float)value) / 360.0;
  data_->set_rotation_z(value);
}

