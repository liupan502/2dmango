#ifndef MANGO_2D_SINGLE_DOOR_GEOMETRY_H_
#define MANGO_2D_SINGLE_DOOR_GEOMETRY_H_

#include "BaseGeometry.h"

#include "InnerWallGeometry.h"

class OpeningData;
class SingleDoorGeometry : public InnerWallGeometry {
public:
  SingleDoorGeometry(OpeningData* openningData );
  //SingleDoorGeometry(float width, float length,OpeningData* openningData = NULL);
  virtual ~SingleDoorGeometry();
  

protected:
  virtual void update_geometry();
  virtual void build_geometry();
private:
  //float width_;
  //float length_;
  PolygonPath* path1_;
  PolygonPath* path2_;
  ArcPath* path3_;
  LinesPath* path4_;
  ContianerPath* contianer_path_;
  const qreal path2_width_ = 20;
  
  


  
  QPolygonF build_path1_polygon();
  QPolygonF build_path2_polygon();
  void build_path3(QRectF& rect,qreal& startAngle,qreal& sweepLength,QPointF& startPoint);
  std::vector<QPointF> build_path4_points();
};
#endif
