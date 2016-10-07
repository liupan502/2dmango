#include "InnerWallGeometry.h"

InnerWallGeometry::InnerWallGeometry() :BaseGeometry() {

}

InnerWallGeometry::InnerWallGeometry(float width, float length):BaseGeometry() {
  width_ = width;
  length_ = length;
}