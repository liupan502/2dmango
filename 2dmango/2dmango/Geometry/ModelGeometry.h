#pragma once
#include "BaseGeometry.h"
#include <QImage>

class BaseGeometryData;
class ModelData;

class ModelGeometry : public BaseGeometry {

public:
  ModelGeometry(ModelData* data);
  virtual void Draw(QPainter* painter);

protected:
  QImage img;
};