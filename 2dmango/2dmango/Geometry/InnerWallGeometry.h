#ifndef MANGO_2D_INNER_WALL_GEOMETRY_H_
#define MANGO_2D_INNER_WALL_GEOMETRY_H_

#include "BaseGeometry.h"
class InnerWallGeometry :public BaseGeometry {
public:
  InnerWallGeometry();
  InnerWallGeometry(float width_, float length_);

protected:
  float width_;
  float length_;
private:
  
};
#endif
