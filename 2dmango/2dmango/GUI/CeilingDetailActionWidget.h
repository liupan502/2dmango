#ifndef MANGO_2D_CEILING_DETAIL_ACTION_WIDGET_H_
#define MANGO_2D_CEILING_DETAIL_ACTION_WIDGET_H_
#include "BaseDetailActionWidget.hpp"
#include <QPushButton>

class CeilingDetailActionWidget :public BaseDetailActionWidget {
  Q_OBJECT
public:
  CeilingDetailActionWidget(QWidget * parent = Q_NULLPTR);
  virtual ~CeilingDetailActionWidget();
  void Init();

  protected slots:
  void OnCeilingBtn1Clicked();

protected:
  QPushButton* ceiling_btn1_;
};

#endif
