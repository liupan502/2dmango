#ifndef MANGO_2D_MOVE_DOOR_GEOMETRY_H_
#define MANGO_2D_MOVE_DOOR_GEOMETRY_H_

#include "BaseGeometry.h"
class MoveDoorGeometry :public BaseGeometry {
public:
  MoveDoorGeometry();
  MoveDoorGeometry(float width, float length);

private:
  float width_;
  float length_;
};
#endif
