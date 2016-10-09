#include "VectorUtil.h"
#include <math.h>

float AngleWithVectors(QVector2D vec1, QVector2D vec2) {
  vec1.setY(-vec1.y());
  vec1.normalize();  
  vec2.setY(-vec2.y());
  vec2.normalize();

  float tmp_value = vec1.x()*vec2.y() - vec1.y()*vec2.x();
  if (tmp_value == 0.0) {
    if (vec1 == vec2) {
      return 0.0;
    }
    else {
      return M_PI;
    }
  }
  float scale = abs(tmp_value) / tmp_value;
  float cos_value = QVector2D::dotProduct(vec1, vec2);
  float radian = scale*acos(cos_value);
  return radian;
}

float AngleOfVector(QVector2D vec) {
  vec.normalize();
  if (vec.isNull()) {
    return 0.0;
  }

  if (vec.x() == 0) {
    if (vec.y() > 0) {
      return M_PI_2;
    }
    else {
      return M_PI + M_PI_2;
    }
  }
  else if (vec.y() == 0) {
    if (vec.x() > 0) {
      return 0.0;
    }
    else {
      return M_PI;
    }
  }  
  
  float cos_value = vec.x() / vec.length();
  float radian = acos(cos_value);
  float sin_value = vec.y() / vec.length();
  if (sin_value < 0) {
    radian = M_PI + radian;
  }
  return radian;
}