#include "WindowGeometry.h"

WindowGeometry::WindowGeometry() :BaseGeometry() {
  width_ = 0.0;
  length_ = 0.0;
}

WindowGeometry::WindowGeometry(float width, float length) : BaseGeometry() {
  width_ = width;
  length_ = length;
}