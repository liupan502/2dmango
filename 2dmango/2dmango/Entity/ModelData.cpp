#include "ModelData.h"
#include <QJsonObject>

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

QJsonObject ModelData::ToJson() {
  QJsonObject object;
  QJsonObject parent_object = BaseGeometryData::ToJson();
  AttachJsonObject(object, parent_object);
  object.insert("model_type", QJsonValue(model_type_));
  object.insert("model_name", QJsonValue(QString(model_name_.c_str())));
  return object;
}

void ModelData::InitWithObject(QJsonObject& jsonObject) {
  BaseGeometryData::InitWithObject(jsonObject);

  if (jsonObject.contains("model_type")) {
    model_type_ = jsonObject["model_type"].toInt();
  }

  if (jsonObject.contains("model_name")) {
    model_name_ = jsonObject["model_name"].toString().toStdString();
  }
}