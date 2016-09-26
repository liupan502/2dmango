#ifndef MANGO_2D_WALL_GEOMETRY_H_
#define MANGO_2D_WALL_GEOMETRY_H_
#include "BaseGeometry.h"

class WallGeometry :public BaseGeometry {
  
  public:
    WallGeometry();
    WallGeometry(QPolygonF polygon);
    WallGeometry(std::vector<QPointF> points);
    

  private:
   
   QPolygonF polygon_;
};
#endif
