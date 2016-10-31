#ifndef MANGO_2D_OPENING_DATA_H_
#define MANGO_2D_OPENING_DATA_H_

#include "BaseData.h"
#include "Geometry/BaseGeometry.h"
#include "Geometry/SingleDoorGeometry.h"


class SingleDoorGeometry;
class DoubleDoorGeometry;
class MoveDoorGeometry;
class WindowGeometry;
class BaseGeometry;
typedef enum OPENING_TYPE {
  OPENING_NONE,
  OPENING_SINGLE_DOOR,
  OPENING_DOUBLE_DOOR,
  OPENING_MOVE_DOOR,
  OPENING_WINDOW,
} OPENING_TYPE;

class OpeningData :public BaseGeometryData {
public:
  OpeningData(std::string name = "");
  OpeningData(SingleDoorGeometry geometry,std::string name = "");
  OpeningData(DoubleDoorGeometry geometry, std::string name = "");
  OpeningData(MoveDoorGeometry geometry, std::string name = "");
  OpeningData(WindowGeometry geometry, std::string name = "");
  BaseGeometry* GetGeometry();
  OPENING_TYPE type();

  QJsonObject virtual ToJson();
  virtual void InitWithObject(QJsonObject& jsonObject);
private:
  OPENING_TYPE opening_type_;
  std::string wall_name_;
  void init_geometry(BaseGeometry geometry);
  
};

#endif
