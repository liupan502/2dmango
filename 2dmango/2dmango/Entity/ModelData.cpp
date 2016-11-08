#include "ModelData.h"

ModelData::ModelData(std::string name) {
  set_name(name);
  model_name_ = "";
  model_type_ = 0;
}

std::string ModelData::model_name() {
  return model_name_;
}

void ModelData::set_model_name(std::string name) {
  model_name_ = name;
}

void ModelData::set_model_type(int modelType) {
  model_type_ = modelType;
}

int ModelData::model_type() {
  return model_type_;
}