#ifndef MANGO_2D_BASE_GEOMETRY_H_
#define MANGO_2D_BASE_GEOMETRY_H_

#include<QVector2D>
#include <QPointF>
#include <QPainter>
#include <vector>
#include "BasePath.h"

class BaseGeometryData;

typedef enum GEOMETRY_TYPE {
  GEOMETRY_NONE,
  GEOMETRY_WALL,
  GEOMETRY_OPENING,
  GEOMETRY_MODEL,
} GEOMETRY_TYPE;
class BaseGeometry {
  public:
   BaseGeometry(BaseGeometryData* data = NULL);
   virtual void Draw(QPainter* painter);
   virtual void MoveTo(QPointF position);
   virtual void Translate(QPointF offset);
   //virtual QTransform ()
   void set_is_visible(bool is_visible);
   bool is_visible();
   virtual bool IsPointIn(QPointF point);
   virtual QRectF Rect();
   //BaseGeometry();

   void set_width(float width);
   void set_height(float height);
   void set_length(float length);
   void set_position(QPointF position);
   void set_rotation(float radian);

   float width();
   float height();
   float length();
   QPointF position();
   float rotation();
   GEOMETRY_TYPE geometry_type();

 protected:
   std::vector<BasePath*> paths_;
   //bool is_visible_;
   int index_;
   //QPointF position_;
   QTransform transform_;
   //float rotate_radian_;

   /*float width_;
   float length_;
   float height_;*/

   BaseGeometryData* data_;
   GEOMETRY_TYPE geometry_type_;
   
   virtual void update_transform();
   virtual void update_geometry();
 private:  
   
   
};
#endif
