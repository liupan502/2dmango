#ifndef MANGO_2D_BASE_DATA_H_
#define MANGO_2D_BASE_DATA_H_

#include <string>
#include <QVector3D>


class BaseData {
  public:
    BaseData() {
      name_ = "";
    }
    BaseData(std::string name) {
      name_ = name;
    }
    void set_name(std::string name){
      name_ = name;
    }

    std::string name() const {
      return name_;
    }

    virtual std::string ToJson() = 0;
  private:
    std::string name_;
};

class BaseGeometryData:public BaseData{
  public:
    BaseGeometryData() {
      length_ = 0.0;
      width_ = 0.0;
      height_ = 0.0;

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
    virtual std::string ToJson() = 0;

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

