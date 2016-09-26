#include "mango2d.h"
#include <QtWidgets/QApplication>
#include "Entity/DesignDataWrapper.h"


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Mango2d w;
  //DesignDataWrapper::my_instance = NULL;
  //w.setWindowFlags(Qt::FramelessWindowHint);
  //w.setAttribute(Qt::WA_TranslucentBackground);
  //w.ui
  //w.ui.
  w.setAutoFillBackground(true);
  QPalette palette;
  palette.setColor(QPalette::Background, QColor(192, 253, 123));
  w.setPalette(palette);
	w.show();
	return a.exec();
}
