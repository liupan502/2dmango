#include "DoubleDoorGeometry.h"

DoubleDoorGeometry::DoubleDoorGeometry() :BaseGeometry() {
  width_ = 0.0;
  length_ = 0.0;
};

DoubleDoorGeometry::DoubleDoorGeometry(float width, float length) {
  width_ = width;
  length_ = length;
}