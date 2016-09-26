#ifndef MANGO_2D_BASE_MOUSE_ADAPTER_H_
#define MANGO_2D_BASE_MOUSE_ADAPTER_H_
#include <QMouseEvent>
#include <QEvent>
#include "Entity/DesignDataWrapper.h"
class BaseActionAdapter {
  public:
    //BaseMouseAdapter();
    virtual void OnMouseMove(QMouseEvent* event);

    virtual void OnMousePress(QMouseEvent* event);

    virtual void OnMouseRelease(QMouseEvent* event);

    virtual void OnMouseLeave(QEvent* event);
  private:
    
};
#endif
