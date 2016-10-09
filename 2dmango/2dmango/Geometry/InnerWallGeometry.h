#ifndef MANGO_2D_INNER_WALL_GEOMETRY_H_
#define MANGO_2D_INNER_WALL_GEOMETRY_H_

#include "BaseGeometry.h"
class InnerWallGeometry :public BaseGeometry {
public:
  InnerWallGeometry();
  InnerWallGeometry(float width_, float length_);
  virtual void MoveTo(QPointF position);
  virtual void Translate(QPointF offset);
  virtual QRectF Rect();
//public signals :
//InnerWallGeometryUpdate();

protected:
  float width_;
  float length_;
  
  void compute_position(QPointF& currentPosition);
private:
  
};
#endif
