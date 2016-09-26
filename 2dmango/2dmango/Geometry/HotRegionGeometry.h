#ifndef MANGO_2D_HOT_REGION_GEOMETRY_H_
#define MANGO_2D_HOT_REGION_GEOMETRY_H_
#include "BaseGeometry.h"
class HotRegionGeometry :public BaseGeometry {

  public:   
    HotRegionGeometry(QPointF center,qreal x,qreal y);
    HotRegionGeometry();
    void MoveTo(QPointF position);
    void Resize(qreal rx,qreal ry);
    bool ContainsPoint(QPointF point);
  private:
  };
#endif
