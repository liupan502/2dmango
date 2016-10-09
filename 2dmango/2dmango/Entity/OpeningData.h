#ifndef MANGO_2D_OPENING_DATA_H_
#define MANGO_2D_OPENING_DATA_H_

#include "BaseData.h"

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

private:
  OPENING_TYPE opening_type_;
};
#endif
