#ifndef MANGO_2D_CEILING_DATA_H_
#define MANGO_2D_CEILING_DATA_H_

#include "BaseData.h"
#include "RoomData.h"

enum CEILING_TYPE {
  CEILING_NONE,
  CEILING_CROSS_SECTION,
};

enum CEILING_UNIT_TYPE {
  CEILING_UNIT_NONE,
  CEILING_UNIT_LINE,
};

class BaseCeilingUnit {
public:
  
  CEILING_UNIT_TYPE ceiling_unit_type();
  virtual QJsonObject ToJson();
  virtual void InitWithObject(QJsonObject& jsonObject);
  virtual QPointF start_point();
  virtual QPointF end_point();
protected:
  CEILING_UNIT_TYPE ceiling_unit_type_;
};

class LineCeilingUnit:public BaseCeilingUnit {
public:
  LineCeilingUnit(QPointF startPoint = QPointF(), QPointF endPoint = QPointF());
  virtual QJsonObject ToJson() ;
  virtual void InitWithObject(QJsonObject& jsonObject);
  virtual QPointF start_point();
  virtual QPointF end_point();
protected:
  QPointF start_point_;
  QPointF end_point_;
};

class BaseCeilingData :public BaseGeometryData {
public:
  BaseCeilingData(CEILING_TYPE type = CEILING_NONE,const std::string& roomName = "");
  CEILING_TYPE ceiling_type();
  virtual QJsonObject ToJson();
  virtual void InitWithObject(QJsonObject& jsonObject);
  void set_room_name(const std::string& roomName);
  std::string room_name();
  //virtual float width();

protected:
  CEILING_TYPE ceiling_type_;
  std::string room_name_;
};

class CrossSectionCeilingData :public BaseCeilingData {
public:
  
  virtual QJsonObject ToJson();
  virtual void InitWithObject(QJsonObject& jsonObject);
  virtual float width();
  static CrossSectionCeilingData* CreateCeilingData1();
  CrossSectionCeilingData();
protected:  
  std::vector<BaseCeilingUnit*> ceiling_units_;
};



class CeilingDataInstance {
public:
  std::string room_name();
  void set_room_name(const std::string& room_name);
protected:
  std::string room_name_;
};
#endif
