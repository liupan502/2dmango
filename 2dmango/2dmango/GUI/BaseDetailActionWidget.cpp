#include "BaseDetailActionWidget.hpp"

BaseDetailActionWidget::BaseDetailActionWidget(QWidget * parent) : QWidget(parent) {
	init();
}

BaseDetailActionWidget::~BaseDetailActionWidget() {
	
}

void BaseDetailActionWidget::init(){
  setGeometry(100,0,200,400);
  setWindowFlags(Qt::FramelessWindowHint);
  setAutoFillBackground(true);
  QPalette palette;
  palette.setColor(QPalette::Background, QColor(255, 0, 255));
  setPalette(palette);
}
