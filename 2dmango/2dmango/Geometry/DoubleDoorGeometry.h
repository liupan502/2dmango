#ifndef MANGO_2D_DOUBLE_DOOR_GEOMETRY_H_
#define MANGO_2D_DOUBLE_DOOR_GEOMETRY_H_

#include "BaseGeometry.h"
#include "InnerWallGeometry.h"

class OpeningData;

class DoubleDoorGeometry : public InnerWallGeometry{
public:
  DoubleDoorGeometry(OpeningData* data = NULL);
  DoubleDoorGeometry(float width, float length,OpeningData* data = NULL);
  virtual ~DoubleDoorGeometry();
  

private:
  //float width_;
  //float length_;
  const qreal path2_width_ = 20;

  PolygonPath* path1_;
  PolygonPath* path2_;
  LinesPath* path3_;
  ArcPath* path4_;
  ContianerPath* contianer_path1_;

  PolygonPath* path6_;
  LinesPath* path7_;
  ArcPath* path8_;
  ContianerPath* contianer_path2_;

  QPolygonF build_path1_polygon();
  QPolygonF build_path2_polygon();
  std::vector<QPointF> build_path3_points();
  void build_path4_params(QRectF& rect, qreal& startAngle, qreal& sweepLength,QPointF& startPoint);  
  QPolygonF build_path6_polygon();
  std::vector<QPointF> build_path7_points();
  void build_path8_params(QRectF& rect, qreal& startAngle, qreal& sweepLength,QPointF& startPoint);

  virtual void update_geometry();

  
};
#endif
