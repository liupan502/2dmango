#ifndef MANGO_2D_SINGLE_DOOR_GEOMETRY_H_
#define MANGO_2D_SINGLE_DOOR_GEOMETRY_H_

#include "BaseGeometry.h"


class SingleDoorGeometry : public BaseGeometry {
public:
  SingleDoorGeometry();
  SingleDoorGeometry(float width, float length);
  virtual ~SingleDoorGeometry();
  

protected:
  virtual void update_geometry();

private:
  float width_;
  float length_;
  PolygonPath* path1_;
  PolygonPath* path2_;
  ArcPath* path3_;
  LinesPath* path4_;
  ContianerPath* contianer_path_;
  const qreal path2_width_ = 20;
  


  void build_geometry(float width, float length);
  QPolygonF build_path1_polygon();
  QPolygonF build_path2_polygon();
  void build_path3(QRectF& rect,qreal& startAngle,qreal& sweepLength,QPointF& startPoint);
  std::vector<QPointF> build_path4_points();
};
#endif
