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
  palette.setColor(QPalette::Background, QColor(192, 253, 123));
  w.setPalette(palette);
	w.show();
  DesignUpdater* updater = new DesignUpdater();
  ShareMemoryBegin(updater);
  QTimer timer;
  QObject::connect(&timer, SIGNAL(timeout()), updater, SLOT(UpdateDesignData()));
  timer.start(1000);
	return a.exec();
}
