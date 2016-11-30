#ifndef MANGO2D_H
#define MANGO2D_H

#include <QtWidgets/QMainWindow>
#include "ui_mango2d.h"
#include "GUI/actionnavgationwidget.h"
#include "GUI/ItemPropertyWidget.h"
#include "GUI/WorkSpaceWidget.hpp"

class Mango2d : public QMainWindow
{
	Q_OBJECT

public:
	Mango2d(QWidget *parent = 0);
	~Mango2d();
  WorkSpaceWidget* work_space_widget();
  ActionNavigationWidget* action_navigation_widget();

private:
	Ui::Mango2dClass ui;
  ActionNavigationWidget* action_navi_widget_;
  WorkSpaceWidget* work_space_widget_;
  ItemPropertyWidget* item_property_widget_;
};

#endif // MANGO2D_H
