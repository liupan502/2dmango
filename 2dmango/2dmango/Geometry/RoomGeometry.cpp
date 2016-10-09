#include "RoomGeometry.h"
#include "Entity/RoomData.h"


RoomGeometry::RoomGeometry(RoomData* roomData) {
  room_data_ = roomData;
}

QVector2D RoomGeometry::WallOutsideDirection(WallData* wallData) {
  QVector2D outside_direction;
  if (room_data_ != NULL) {
    outside_direction = room_data_->WallOutsideDirection(wallData);
  }
  return outside_direction;
}
