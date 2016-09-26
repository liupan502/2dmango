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

    std::string name(){
      return name_;
    }

    virtual std::string ToJson() = 0;
  private:
    std::string name_;
};

class BaseGeometryData:public BaseData{
  public:

    void set_length(int length){
      length_ = length;
    }

    int length(){
      return length_;
    }

    void set_width(int width){\
      width_ = width;
    }

    int width(){
      return width_;
    }

    void set_height(int height){
      height_ = height;
    }

    int height(){
      return height_;
    }


    virtual void set_position(QVector3D position){
      position_ = position;
    }

    QVector3D position(){
      return position_;
    }
    virtual std::string ToJson() = 0;

  private:
    int length_;
    int width_;
    int height_;

    QVector3D position_;

};
#endif // !MANGO_2D_Base_DATA_H_

