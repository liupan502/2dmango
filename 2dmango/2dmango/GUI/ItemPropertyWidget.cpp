#include "ItemPropertyWidget.h"
#include <QPushButton>
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
  setGeometry(0, 50, 300, 600);
  setAutoFillBackground(true);
  QPalette palette;
  palette.setColor(QPalette::Background, QColor(0, 0, 255));
  setPalette(palette);
  setWindowFlags(Qt::FramelessWindowHint);

  QPushButton* base_draw_house_btn_ = new QPushButton(this);
  base_draw_house_btn_->setGeometry(0, 0, 100, 50);
  base_draw_house_btn_->setText(QString::fromLocal8Bit("»­»§ÐÍ"));
}

OpeningPropertyDetailWidget::OpeningPropertyDetailWidget(QWidget * parent ) {
  init();
}

OpeningPropertyDetailWidget::~OpeningPropertyDetailWidget() {

}

void OpeningPropertyDetailWidget::set_data(BaseGeometryData* data) {
  if (data_->geometry_type() != GEOMETRY_OPENING)
    return;
  data_ = data;
}

void OpeningPropertyDetailWidget::UpdateContent(bool isViewToData) {

}

void OpeningPropertyDetailWidget::init() {

}

ModelPropertyDetailWidget::ModelPropertyDetailWidget(QWidget * parent ) {
  init();
}

ModelPropertyDetailWidget::~ModelPropertyDetailWidget() {

}

void ModelPropertyDetailWidget::set_data(BaseGeometryData* data) {
  if (data->geometry_type() != GEOMETRY_MODEL)
    return;
  data_ = data;
}

void ModelPropertyDetailWidget::UpdateContent(bool isViewToData) {

}

void ModelPropertyDetailWidget::init() {

}

