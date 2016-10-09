#ifndef  MANGO_2D_ROOM_GEOMETRY_H_

#include "BaseGeometry.h"


class RoomData;
class WallData;
class RoomGeometry :public BaseGeometry {
public:
  //RoomGeometry();
  RoomGeometry(RoomData* roomData = NULL);

  QVector2D WallOutsideDirection(WallData* wallData);

private:
  RoomData* room_data_;
};
#endif // ! MANGO_2D_ROOM_GEOMETRY_H_

