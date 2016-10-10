#ifndef MANGO_2D_INNER_WALL_GEOMETRY_H_
#define MANGO_2D_INNER_WALL_GEOMETRY_H_

#include "BaseGeometry.h"
#include "Entity/OpeningData.h"

class BaseGeometryData;
class InnerWallGeometry :public BaseGeometry {
public:
  InnerWallGeometry(BaseGeometryData* data = NULL);
  InnerWallGeometry(float width_, float length_, BaseGeometryData* data = NULL);
  virtual void MoveTo(QPointF position);
  virtual void Translate(QPointF offset);
  virtual QRectF Rect();
  OPENING_TYPE opening_type();
//public signals :
//InnerWallGeometryUpdate();

protected:
  //float width_;
  //float length_;
  virtual void init_with_data(BaseGeometryData* data);
  void compute_position(QPointF& currentPosition);
  OPENING_TYPE opening_type_;
  OpeningData* opening_data_;
  //void virtual update_geometry();
private:
  
};
#endif
