#include "InnerWallGeometry.h"
#include "Entity/DesignDataWrapper.h"
#include "Util/LineUtil.h"
#include "Util/VectorUtil.h"
#include <math.h>
#include "Entity/BaseData.h"
#include "Entity/OpeningData.h"

InnerWallGeometry::InnerWallGeometry(OpeningData* data):BaseGeometry(data) {  
  geometry_type_ = GEOMETRY_OPENING;
  opening_type_ = OPENING_NONE;
  //opening_data_ = NULL;
  //init_with_data(data);
}

/*InnerWallGeometry::InnerWallGeometry(float width, float length, BaseGeometryData* data):BaseGeometry(data) {
  width_ = width;
  length_ = length;
  rotate_radian_ = 0.0;
  init_with_data(data);
  geometry_type_ = GEOMETRY_OPENING;
  opening_type_ = OPENING_NONE;
}*/

void InnerWallGeometry::MoveTo(QPointF position) {
  compute_position(position);
  BaseGeometry::MoveTo(position);
}

void InnerWallGeometry::Translate(QPointF offset) {
  QPointF position = this->position() + offset;
  compute_position(position);
  BaseGeometry::MoveTo(position);
}

void InnerWallGeometry::compute_position(QPointF& position) {
  DesignDataWrapper* instance = DesignDataWrapper::GetInstance();
  qreal distance;
  WallGeometry wall_geometry;
  if (!instance->GetClosestWall(position, distance, wall_geometry)) {
    return;
  }

  if (distance < 30) {
    QLineF line1 = wall_geometry.Line1();
    QLineF line2 = wall_geometry.Line2();
    QLineF line = line1.length() < line2.length() ? line1 : line2;
    QLineF normal_line = NormalLineWithPoint(line, position);
    QPointF tmp_point;
    normal_line.intersect(line, &tmp_point);
    qreal distance1 = QVector2D(tmp_point - line.p1()).length();
    qreal distance2 = QVector2D(tmp_point - line.p2()).length();
    qreal distance = distance1 < distance2 ? distance1 : distance2;
    QRectF rect = Rect();
    qreal half_length = rect.width()/2.0;
    if (distance > half_length) {
      //QVector2D wall_vector = wall_geometry.WallVector();      
      //rotate_radian_ = acosf(wall_vector.x()/wall_vector.length());
      QVector2D vec(0, -1);
      QVector2D wall_normal_vector = wall_geometry.NormalVector();
      set_rotation(AngleWithVectors(wall_normal_vector, vec));      
      QPointF tmp_point1, tmp_point2;
      normal_line.intersect(line1, &tmp_point1);
      normal_line.intersect(line2, &tmp_point2);
      position = (tmp_point1 + tmp_point2) / 2.0;
    }
   }

  else {

  }
}

QRectF InnerWallGeometry::Rect() {
  QRectF rect;
  qreal half_width = width() / 2.0;
  qreal half_length = length() / 2.0;
  QPointF top_left_point = position() - QPointF(half_length, half_width);
  QPointF bottom_right_point = position() + QPointF(half_length, half_width);
  rect = QRectF(top_left_point, bottom_right_point);
  
  return rect;
}

/*void InnerWallGeometry::init_with_data(OpeningData* data) {
  if (data == NULL) {
    return;
  }
  set_width(data->width());
  set_length(data->length());
  set_rotation(data->rotation_z());
  QVector3D tmp_vec3d = data->position();
  QPointF tmp_point = QPointF(tmp_vec3d.x(), tmp_vec3d.y());
  set_position(tmp_point);
  opening_type_ = data->type();
  opening_data_ = data;
}*/

OPENING_TYPE InnerWallGeometry::opening_type() {
  return opening_type_;
}

