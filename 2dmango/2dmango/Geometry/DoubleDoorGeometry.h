#ifndef MANGO_2D_SINGLE_DOOR_GEOMETRY_H_
#define MANGO_2D_DOUBLE_DOOR_GEOMETRY_H_

#include "BaseGeometry.h"

class DoubleDoorGeometry : public BaseGeometry{
public:
  DoubleDoorGeometry();
  DoubleDoorGeometry(float width, float length);

private:
  float width_;
  float length_;
};
#endif
