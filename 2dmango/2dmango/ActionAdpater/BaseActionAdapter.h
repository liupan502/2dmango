#ifndef MANGO_2D_BASE_MOUSE_ADAPTER_H_
#define MANGO_2D_BASE_MOUSE_ADAPTER_H_
#include <QMouseEvent>
#include <QEvent>
#include "Entity/DesignDataWrapper.h"


enum MOVESTATUS {
  NO_MOVE,
  DOWN_MOVE,
  UP_MOVE
};
class BaseActionAdapter:public QObject {
  public:
    BaseActionAdapter();

    virtual void OnMouseMove(QMouseEvent* event);

    virtual void OnMousePress(QMouseEvent* event);

    virtual void OnMouseRelease(QMouseEvent* event);

    virtual void OnMouseLeave(QEvent* event);

protected:
  bool is_left_mouse_down_;
  MOVESTATUS move_status_;
  private:
    
};
#endif
