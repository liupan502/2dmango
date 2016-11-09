#ifndef MANGO_2D_BASE_DATA_H_
#define MANGO_2D_BASE_DATA_H_

#include <string>
#include <QVector3D>
#include <QJsonObject>
#include "Util/JsonUtil.h"


class BaseData {
  public:
    BaseData(std::string name = "") {
      name_ = name;
      is_tmp_data_ = false;
      is_visible_ = true;
    }

    BaseData(std::string name) {
      name_ = name;
    }

    bool is_visible() {
      return is_visible_;
    }

    void set_is_visible(bool isVisible) {
      is_visible_ = isVisible;
    }

    void set_name(std::string name){
      name_ = name;
    }

    std::string name() const {
      return name_;
    }

    bool is_tmp_data() {
      return is_tmp_data_;
    }

    virtual QJsonObject ToJson() {
      QJsonObject object;
      object.insert("name", QJsonValue(name_.c_str()));
      return object;
    };

    virtual void InitWithObject(QJsonObject& jsonObject) {
      if (jsonObject.contains("name")) {
        name_ = jsonObject["name"].toString().toStdString();
      }
      else {
        name_ = "";
      }
    }
protected:
  bool is_tmp_data_;
  bool is_visible_;

private:
    std::string name_;
    
};

class BaseGeometryData:public BaseData{
  public:
    BaseGeometryData(std::string name = ""):BaseData(name) {
      length_ = 0.0;
      width_ = 0.0;
      height_ = 0.0;


      
      is_tmp_data_ = true;

      position_ = QVector3D();
       
      rotation_x_ = 0.0;
      rotation_y_ = 0.0;
      rotation_z_ = 0.0;
    }    

    void set_length(float length){
      length_ = length;
    }

    float length(){
      return length_;
    }

    void set_width(float width){
      width_ = width;
    }

    float width(){
      return width_;
    }

    void set_height(float height){
      height_ = height;
    }

    float height(){
      return height_;
    }

    void set_rotation_z(float rotationZ) {
      rotation_z_ = rotationZ;
    }

    float rotation_z() {
      return rotation_z_;
    }

    void set_rotation_x(float rotationX) {
      rotation_x_ = rotationX;
    }

    float ratation_x() {
      return rotation_x_;
    }

    void set_rotation_y(float rotationY) {
      rotation_y_ = rotationY;
    }

    float rotation_y() {
      return rotation_y_;
    }


    virtual void set_position(QVector3D position){
      position_ = position;
    }

    QVector3D position(){
      return position_;
    }

    virtual QJsonObject ToJson() {
      QJsonObject object;
      QJsonObject parent_object = BaseData::ToJson();
      AttachJsonObject(object, parent_object);
      object.insert("length", QJsonValue(length_));
      object.insert("width", QJsonValue(width_));
      object.insert("height", QJsonValue(height_));

      object.insert("rotation_x", QJsonValue(rotation_x_));
      object.insert("rotation_y", QJsonValue(rotation_y_));
      object.insert("rotation_z", QJsonValue(rotation_z_));

      QString position_str = QVector3DToString(position_);
      object.insert("position", position_str);
      return object;
    }

    virtual void InitWithObject(QJsonObject& jsonObject) {
      BaseData::InitWithObject(jsonObject);
      
      is_tmp_data_ = false;


      if (jsonObject.contains("length")) {
        length_ = jsonObject["length"].toDouble();
      }
      else {
        length_ = 0.0;
      }

      if (jsonObject.contains("width")) {
        width_ = jsonObject["width"].toDouble();
      }
      else {
        width_ = 0.0;
      }

      if (jsonObject.contains("height")) {
        height_ = jsonObject["height"].toDouble();
      }
      else {
        height_ = 0.0;
      }

      if (jsonObject.contains("rotation_x")) {
        rotation_x_ = jsonObject["rotation_x"].toDouble();
      }
      else {
        rotation_x_ = 0.0;
      }

      if (jsonObject.contains("rotation_y")) {
        rotation_y_ = jsonObject["rotation_y"].toDouble();
      }
      else {
        rotation_y_ = 0.0;
      }

      if (jsonObject.contains("rotation_z")) {
        rotation_z_ = jsonObject["rotation_z"].toDouble();
      }
      else {
        rotation_z_ = 0.0;
      }

      if (jsonObject.contains("position")) {
        QString position_str = jsonObject["position"].toString();
        position_ = StringToQVector3D(position_str);
      }
      else {
        position_ = QVector3D();
      }
    }

  protected:
    float length_;
    float width_;
    float height_;

    float rotation_x_;
    float rotation_y_;
    float rotation_z_;

    QVector3D position_;

};
#endif // !MANGO_2D_Base_DATA_H_

