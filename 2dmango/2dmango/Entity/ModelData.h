#ifndef MANGO_2D_MODEL_DATA_H_
#define MANGO_2D_MODEL_DATA_H_

#include "BaseData.h"

class ModelData :public BaseGeometryData {
public:
  ModelData(std::string name = "");
  std::string model_name();
  void set_model_name(std::string name);
  int model_type();
  void set_model_type(int modelType);
private:
  int model_type_;
  std::string model_name_;
};
#endif
