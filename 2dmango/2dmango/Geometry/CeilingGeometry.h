#ifndef MANGO_2D_CEILING_GEOMETRY_H_
#define MANGO_2D_CEILING_GEOMETRY_H_

#include "BaseGeometry.h"

class RoomData;
class BaseCeilingData;
class CeilingGeometry :public BaseGeometry {
public:
  CeilingGeometry(BaseCeilingData* ceilingData = NULL, RoomData* room = NULL);
  virtual ~CeilingGeometry();
  
 
protected:

  std::vector<QPointF> default_polygon(QPointF offset = QPointF());
  RoomData* room_data_;  
  std::vector<QPointF> polygon_;
  virtual void build_geometry();

};
#endif
