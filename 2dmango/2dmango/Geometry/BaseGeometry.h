#ifndef MANGO_2D_BASE_GEOMETRY_H_
#define MANGO_2D_BASE_GEOMETRY_H_

#include<QVector2D>
#include <QPointF>
#include <QPainter>
#include <vector>
#include "BasePath.h"
class BaseGeometry {
  public:
   virtual void Draw(QPainter* painter);
   virtual void MoveTo(QPointF position);
   virtual void Translate(QPointF offset);
   void set_is_visible(bool is_visible);
   bool is_visible();
   virtual bool IsPointIn(QPointF point);
   virtual QRectF rect();
   BaseGeometry();
 protected:
   std::vector<BasePath*> paths_;
   bool is_visible_;
   int index_;
   QPointF position_;
   
   virtual void update_geometry();
 private:  
   
   
};
#endif
