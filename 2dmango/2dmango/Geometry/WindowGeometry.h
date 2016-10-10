#ifndef MANGO_2D_WINDOW_GEOMETRY_H_
#define MANGO_2D_WINDOW_GEOMETRY_H_

#include "BaseGeometry.h"
#include "InnerWallGeometry.h"

class OpeningData;
class WindowGeometry :public InnerWallGeometry {
public:
  WindowGeometry(OpeningData* data = NULL);
  WindowGeometry(float width, float length,OpeningData* data = NULL);
  ~WindowGeometry();
  

private:
  float width_, length_;
  PolygonPath* path1_;
  PolygonPath* path2_;
  QPolygonF build_path1_polygon();
  QPolygonF build_path2_polygon();

  virtual void update_geometry();
};
#endif
