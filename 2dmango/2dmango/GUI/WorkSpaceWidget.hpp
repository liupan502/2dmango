#pragma once
#include <QWidget>
#include "ActionAdpater/BaseActionAdapter.h"
#include "ActionAdpater/DrawWallActionAdapter.h"

typedef enum WORK_MODE{
  NONE_WORK_MODE,
  BASE_HOUSE_WORK_MODE,
} WORK_MODE;

class WorkSpaceWidget : public QWidget {
	Q_OBJECT

public:
	WorkSpaceWidget(QWidget * parent = Q_NULLPTR);
	~WorkSpaceWidget();

  void SwitchWorkMode(WORK_MODE mode);
  void BeginDrawWall();

protected:
  virtual void paintEvent(QPaintEvent* event);
  virtual void leaveEvent(QEvent* event);
  virtual void mouseMoveEvent(QMouseEvent* event);
  virtual void mousePressEvent(QMouseEvent* event);
  virtual void mouseReleaseEvent(QMouseEvent* event);

private:
	void init();
  WORK_MODE work_mode_;

  BaseActionAdapter* mouse_adapter_;
  DrawWallActionAdapter* draw_wall_mouse_adapter_;
};
