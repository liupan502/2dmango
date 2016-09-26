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
   void set_is_visible(bool is_visible);
   bool is_visible();
   BaseGeometry();
 protected:
   std::vector<BasePath*> paths_;
   bool is_visible_;
   int index_;
 private:  
   
   
};
#endif
