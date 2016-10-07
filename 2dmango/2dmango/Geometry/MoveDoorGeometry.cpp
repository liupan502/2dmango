#include "MoveDoorGeometry.h"

MoveDoorGeometry::MoveDoorGeometry() :BaseGeometry() {
  width_ = 0.0;
  length_ = 0.0;
}

MoveDoorGeometry::MoveDoorGeometry(float width, float length) : BaseGeometry() {
  width_ = width;
  length_ = length;
}