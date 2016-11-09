#ifndef MANGO_2D_WALL_GEOMETRY_H_
#define MANGO_2D_WALL_GEOMETRY_H_
#include "BaseGeometry.h"

class WallData;

class WallGeometry :public BaseGeometry {
  
  public:
    WallGeometry();
    WallGeometry(QPolygonF polygon);
    WallGeometry(std::vector<QPointF> points,WallData* wallData);
    bool PointDistanceToGeometry(QPointF position, qreal& distance);
    QLineF Line1();
    QLineF Line2();
    QVector2D WallVector();
    QVector2D NormalVector();
    WallData* wall_data();
  private:   
   QPolygonF polygon_;
   //WallData* wall_data_;
};
#endif
