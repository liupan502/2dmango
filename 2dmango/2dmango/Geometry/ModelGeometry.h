#pragma once
#include "BaseGeometry.h"
#include <QImage>
#include <string>

class BaseGeometryData;
class ModelData;

class ModelGeometry : public BaseGeometry {

public:
  ModelGeometry(ModelData* data = NULL);
  
  virtual void Draw(QPainter* painter);
  virtual bool IsPointIn(const QPointF& point);

protected:
  QImage img;
  std::string model_id_;
  std::string model_name_;
  QPainterPath model_path_;
};