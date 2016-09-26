#ifndef MANGO_2D_ACTION_NAVIGATION_WIDGET_H_
#define MANGO_2D_ACTION_NAVIGATION_WIDGET_H_
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include "BaseDetailActionWidget.hpp"
#include "DrawHouseDetailActionWidget.hpp"

typedef enum ACTION_TYPE {
  DRAW_WALL,
} ACTION_TYPE;

class ActionNavigationWidget : public QWidget {
	Q_OBJECT

public:
  ActionNavigationWidget(QWidget * parent = Q_NULLPTR);
	~ActionNavigationWidget();

private slots:
  void OnDrawHouseClicked();
private:
	void Init();
  ACTION_TYPE action_type_;
  BaseDetailActionWidget* detail_action_widget_;
  QPushButton* base_draw_house_btn_;
  DrawHouseDetailActionWidget* draw_house_detail_action_widget_;
};
#endif
