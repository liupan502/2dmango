#ifndef MANGO_2D_DRAW_HOUSE_DETAIL_ACTION_WIDGET_H_
#define MANGO_2D_DRAW_HOUSE_DETAIL_ACTION_WIDGET_H_
#include "BaseDetailActionWidget.hpp"
#include <QPushButton>

class DrawHouseDetailActionWidget : public BaseDetailActionWidget {
	Q_OBJECT

public:
	DrawHouseDetailActionWidget(QWidget * parent = Q_NULLPTR);
	~DrawHouseDetailActionWidget();
signals:
  void BeginDrawWall();

protected slots:  
  void OnDrawWallBtnClicked();

private:
	void init();
  QPushButton* draw_wall_btn_;
};
#endif
