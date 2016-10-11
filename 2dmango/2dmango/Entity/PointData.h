#ifndef MANGO_2D_POINT_DATA_H_
#define MANGO_2D_POINT_DATA_H_
#include "BaseData.h"

class PointData :public BaseData {
  public:
   PointData();
   PointData(std::string name,QPointF point);
   void set_point(QPointF point);
   QPointF point();
   void Reset();
   bool has_point_data();
   virtual QJsonObject ToJson();
  private:
   QPointF point_;
   
   bool is_generated_;
   bool has_point_data_;
};
#endif
