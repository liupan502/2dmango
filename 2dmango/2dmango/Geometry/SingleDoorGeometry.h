#ifndef MANGO_2D_SINGLE_DOOR_GEOMETRY_H_
#define MANGO_2D_SINGLE_DOOR_GEOMETRY_H_

#include "BaseGeometry.h"


class SingleDoorGeometry : public BaseGeometry {
public:
  SingleDoorGeometry();
  SingleDoorGeometry(float width, float length);

protected:
  virtual void update_geometry();

private:
  float width_;
  float length_;
  PolygonPath* path1_;
  PolygonPath* path2_;
  


  void build_geometry(float width, float length);
  QPolygonF build_path1_polygon();
  QPolygonF build_path2_polygon();
  BasePath* build_path3(float width, float length);
};
#endif
