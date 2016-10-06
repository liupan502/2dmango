#ifndef MANGO_2D_DEFAULT_ACTION_ADAPTER_H_
#define MANGO_2D_DEFAULT_ACTION_ADAPTER_H_

#include "BaseActionAdapter.h"
#include "Geometry/BaseGeometry.h"
class DefaultActionAdapter : public BaseActionAdapter {
  public:
    DefaultActionAdapter();

    virtual void OnMouseMove(QMouseEvent* event);

    virtual void OnMousePress(QMouseEvent* event);

    virtual void OnMouseRelease(QMouseEvent* event);

    virtual void OnMouseLeave(QEvent* event);
 private:
   BaseGeometry* current_selected_geometry_;
   bool left_mouse_down_;
};
#endif
