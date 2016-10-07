#ifndef MANGO_2D_MOVE_DOOR_GEOMETRY_H_
#define MANGO_2D_MOVE_DOOR_GEOMETRY_H_

#include "BaseGeometry.h"
#include "InnerWallGeometry.h"
class MoveDoorGeometry :public InnerWallGeometry {
public:
  MoveDoorGeometry();
  MoveDoorGeometry(float width, float length);
  ~MoveDoorGeometry();  

private:
  //float width_;
  //float length_;
  const qreal path2_offset = 5;

  PolygonPath* path1_;
  PolygonPath* path2_;
  PolygonPath* path3_;

  QPolygonF build_path1_polygon();
  QPolygonF build_path2_polygon();
  QPolygonF build_path3_polygon();

  virtual void update_geometry();
};
#endif
