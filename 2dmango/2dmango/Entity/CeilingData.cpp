#include "CeilingData.h"
#include <QJsonArray>

BaseCeilingUnit* CreateCeilingUnit(QJsonObject& jsonObject) {
  BaseCeilingUnit* ceiling_unit = NULL;
  CEILING_UNIT_TYPE type = CEILING_UNIT_NONE;
  if (jsonObject.contains("ceiling_unit_type")) {
    type = (CEILING_UNIT_TYPE)(jsonObject["ceiling_unit_type"].toInt());
  }

  switch (type)  {  
    case CEILING_UNIT_LINE:
      ceiling_unit = (BaseCeilingUnit*)(new LineCeilingUnit());
      break;
    default:
      ceiling_unit = new BaseCeilingUnit();
      break;
  }
  ceiling_unit->InitWithObject(jsonObject);
  return ceiling_unit;
}

CEILING_UNIT_TYPE BaseCeilingUnit::ceiling_unit_type() {
  return ceiling_unit_type_;
}

QJsonObject BaseCeilingUnit::ToJson() {
  QJsonObject object;
  object.insert("ceiling_unit_type", QJsonValue((int)ceiling_unit_type()));
  return object;
}

void BaseCeilingUnit::InitWithObject(QJsonObject& jsonObject) {
  if (jsonObject.contains("ceiling_unit_type")) {
    ceiling_unit_type_ = (CEILING_UNIT_TYPE)jsonObject["ceiling_unit_type"].toInt();
  }
  else {
    ceiling_unit_type_ = CEILING_UNIT_NONE;
  }
}

QPointF BaseCeilingUnit::start_point() {
  return QPointF();
}

QPointF BaseCeilingUnit::end_point() {
  return QPointF();
}

LineCeilingUnit::LineCeilingUnit(QPointF startPoint , QPointF endPoint ) {
  start_point_ = startPoint;
  end_point_ = endPoint;
  ceiling_unit_type_ = CEILING_UNIT_LINE;
}

QPointF LineCeilingUnit::start_point() {
  return start_point_;
}

QPointF LineCeilingUnit::end_point() {
  return end_point_;
}

QJsonObject LineCeilingUnit::ToJson() {
  QJsonObject object;
  QJsonObject parent_object = BaseCeilingUnit::ToJson();
  AttachJsonObject(object, parent_object);
  object.insert("start_point", QJsonValue(QVector2DToString(QVector2D(start_point()))));
  object.insert("end_point", QJsonValue(QVector2DToString(QVector2D(end_point()))));
  return object;
}

void LineCeilingUnit::InitWithObject(QJsonObject& jsonObject) {
  BaseCeilingUnit::InitWithObject(jsonObject);
  if (jsonObject.contains("start_point")) {    
    start_point_ = StringToQVector2D(jsonObject["start_point"].toString()).toPointF();
  }
  else {
    start_point_ = QPointF();
  }

  if (jsonObject.contains("end_point")) {
    end_point_ = StringToQVector2D(jsonObject["end_point"].toString()).toPointF();
  }
  else {
    end_point_ = QPointF();
  }
}

std::string CeilingDataInstance::room_name(){
  return room_name_;
}

void CeilingDataInstance::set_room_name(const std::string& room_name){
  room_name_ = room_name;
}

BaseCeilingData::BaseCeilingData(CEILING_TYPE type, const std::string& roomName) {
  ceiling_type_ = type;
  room_name_ = roomName;
  geometry_type_ = GEOMETRY_CEILING;
}

CEILING_TYPE BaseCeilingData::ceiling_type() {
  return ceiling_type_;
}

QJsonObject BaseCeilingData::ToJson() {
  QJsonObject object;
  QJsonObject parent_object = BaseData::ToJson();
  AttachJsonObject(object, parent_object);
  object.insert("ceiling_type", QJsonValue(ceiling_type()));
  object.insert("room_name", QJsonValue(QString::fromStdString(room_name())));
  return object;
}

void BaseCeilingData::InitWithObject(QJsonObject& jsonObject) {
  BaseData::InitWithObject(jsonObject);
  if (jsonObject.contains("ceiling_type")) {
    ceiling_type_ = (CEILING_TYPE)(jsonObject["ceiling_type"].toInt());
  }
  else {
    ceiling_type_ = CEILING_NONE;
  }

  if (jsonObject.contains("room_name")) {
    set_room_name(jsonObject["room_name"].toString().toStdString());
  }
  else {
    set_room_name("");
  }
  
}

void BaseCeilingData::set_room_name(const std::string& roomName) {
  room_name_ = roomName;
}

std::string BaseCeilingData::room_name() {
  return room_name_;
}

CrossSectionCeilingData::CrossSectionCeilingData():BaseCeilingData(CEILING_CROSS_SECTION){

}

QJsonObject CrossSectionCeilingData::ToJson() {
  QJsonObject object;
  QJsonObject parent_object = BaseCeilingData::ToJson();
  AttachJsonObject(object, parent_object);
  //object.insert("ceiling_type", QJsonValue(ceiling_type()));
  QJsonArray ceiling_unit_jsons;
  for (int i = 0; i < ceiling_units_.size(); i++) {
    QJsonObject unit_object = ceiling_units_[i]->ToJson();
    ceiling_unit_jsons.append(QJsonValue(unit_object));
  }
  object.insert("ceiling_units", QJsonValue(ceiling_unit_jsons));
  return object;
}

void CrossSectionCeilingData::InitWithObject(QJsonObject& jsonObject) {
  BaseCeilingData::InitWithObject(jsonObject);
  if (jsonObject.contains("ceiling_units")) {
    for (int i = 0; i < ceiling_units_.size(); i++) {
      delete ceiling_units_[i];
      ceiling_units_[i] = NULL;
    }
    ceiling_units_.clear();
    QJsonArray array = jsonObject["ceiling_units"].toArray();
    for (int i = 0; i < array.count(); i++) {
      QJsonObject unit_object = array.at(i).toObject();
      ceiling_units_.push_back(CreateCeilingUnit(unit_object));
    }
  }
}

float CrossSectionCeilingData::width() {
  //return 20;
  if (ceiling_units_.size() < 1)
    return 0;
  float x_min = ceiling_units_[0]->start_point().x();
  float x_max = x_min;
  for (int i = 0; i < ceiling_units_.size(); i++) {
    float start_point_x = ceiling_units_[i]->start_point().x();
    if (start_point_x < x_min) {
      x_min = start_point_x;
    }

    if (start_point_x > x_max) {
      x_max = start_point_x;
    }

    float end_point_x = ceiling_units_[i]->end_point().x();
    if (end_point_x < x_min) {
      x_min = end_point_x;
    }

    if (end_point_x > x_max) {
      x_max = end_point_x;
    }
  }
  return abs(x_max-x_min);
}

CrossSectionCeilingData* CrossSectionCeilingData::CreateCeilingData1() {
  CrossSectionCeilingData* data = new CrossSectionCeilingData();

  LineCeilingUnit* line1 = new LineCeilingUnit(QPointF(0.0, 0.0), QPointF(0.0, 25.0));
  LineCeilingUnit* line2 = new LineCeilingUnit(QPointF(0.0, 25.0), QPointF(40.0, 25.0));
  LineCeilingUnit* line3 = new LineCeilingUnit(QPointF(40.0, 25.0), QPointF(40.0, 15.0));
  LineCeilingUnit* line4 = new LineCeilingUnit(QPointF(40.0, 15.0), QPointF(30.0, 15.0));
  LineCeilingUnit* line5 = new LineCeilingUnit(QPointF(30.0, 15.0), QPointF(30.0, 0.0));

  data->ceiling_units_.push_back(line1);
  data->ceiling_units_.push_back(line2);
  data->ceiling_units_.push_back(line3);
  data->ceiling_units_.push_back(line4);
  data->ceiling_units_.push_back(line5);
  
  return data;
}





