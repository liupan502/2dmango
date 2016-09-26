
#ifndef MANGO_2D_BASE_DETAIL_ACTION_WIDGET_H_
#define MANGO_2D_BASE_DETAIL_ACTION_WIDGET_H_
#include <QWidget>

class BaseDetailActionWidget : public QWidget {
	Q_OBJECT

public:
	BaseDetailActionWidget(QWidget * parent = Q_NULLPTR);
	~BaseDetailActionWidget();
  
private:
  void init();
};

#endif
