#include "BaseDetailActionWidget.hpp"

BaseDetailActionWidget::BaseDetailActionWidget(QWidget * parent) : QWidget(parent) {
	init();
}

BaseDetailActionWidget::~BaseDetailActionWidget() {
	
}

void BaseDetailActionWidget::init(){
  setGeometry(100,0,200,600);
  setWindowFlags(Qt::FramelessWindowHint);
  setAutoFillBackground(true);
  QPalette palette;
  palette.setColor(QPalette::Background, QColor("#cfcfcf"));
  setPalette(palette);
}
