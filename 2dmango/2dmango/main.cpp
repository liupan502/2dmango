#include "mango2d.h"
#include <QtWidgets/QApplication>
#include "Entity/DesignDataWrapper.h"
#include "Util/ShareMemoryUtil.h"


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Mango2d w;  
  w.setAutoFillBackground(true);
  QPalette palette;
  //palette.setColor(QPalette::Background, QColor(0, 0, 0));
  //QColor color;
  //color.setNamedColor("#ededed");
  palette.setColor(QPalette::Background, QColor("#ededed"));
  QPixmap log_pixmap = QPixmap(241, 40);
  log_pixmap.load("./icon/logo.png");
  QIcon logo_icon = QIcon(log_pixmap);
  QPushButton* logo_btn = new QPushButton(logo_icon,"",&w);
  logo_btn->setIconSize(QSize(294, 50));
  logo_btn->setGeometry(0, 0, 294, 50);
  logo_btn->setPalette(palette);
  logo_btn->setWindowFlags(Qt::FramelessWindowHint);//ÎÞ±ß¿ò
  logo_btn->setAttribute(Qt::WA_TranslucentBackground);//±³¾°Í¸Ã÷

  w.setPalette(palette);
	w.show();
  DesignUpdater* updater = new DesignUpdater();
  ShareMemoryBegin(updater);
  QTimer timer;
  QObject::connect(&timer, SIGNAL(timeout()), updater, SLOT(UpdateDesignData()));
  timer.start(1000);
	return a.exec();
}
