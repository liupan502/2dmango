#ifndef MANGO_2D_LINE_DATA_H_
#define MANGO_2D_LINE_DATA_H_
#include "BaseData.h"
#include <QVector2D>
#include <QLineF>

class LineData :public BaseData {
  public:
   LineData();

   LineData(std::string lineName ,std::string startPointName = " ",std::string endPointName = " ",bool is_independent = true);
   
   std::string start_point_name();

   void set_start_point_name(std::string name);

   std::string end_point_name();

   void set_end_point_name(std::string name);

   bool is_independent();

   void set_is_independent(bool is_independent);

   std::string find_connected_point(LineData line);
   
   bool DoCotainPoint(std::string pointName);

   bool IsStartPoint(std::string pointName);

   bool IsEndPoint(std::string pointName);

   void set_line(QLineF line);

   void Reset();

   QLineF Line();

   bool IsAvailable();

   virtual QJsonObject ToJson();

   virtual void InitWithObject(QJsonObject& jsonObject);

   QPointF Intersect(LineData line);

 private:
   std::string start_point_name_;
   std::string end_point_name_;
   bool is_independent_;

   //QPointF point_;
   //QVector2D vec_;
   QLineF line_;
};
#endif
