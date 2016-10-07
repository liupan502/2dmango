#ifndef MANGO_2D_WINDOW_GEOMETRY_H_
#define MANGO_2D_WINDOW_GEOMETRY_H_

#include "BaseGeometry.h"

class WindowGeometry :public BaseGeometry {
public:
  WindowGeometry();
  WindowGeometry(float width, float length);

private:
  float width_;
  float length_;
};
#endif
