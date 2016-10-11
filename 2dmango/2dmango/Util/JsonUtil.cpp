#include "JsonUtil.h"
#include <QStringList>
#include <QJsonValue>

void AttachJsonObject(QJsonObject& obj1, QJsonObject& obj2) {
  QStringList keys = obj2.keys();
  for (int i = 0; i < keys.size(); i++) {
    QString key = keys[i];
    QJsonValue value = obj2[key];
    obj1.insert(key, value);
  }
}

QString QVector3DToString(QVector3D vec3d) {
  
  QString x_str;
  x_str.clear();
  x_str = x_str.setNum(vec3d.x());

  QString y_str;
  y_str.clear();
  y_str = y_str.setNum(vec3d.y());

  QString z_str;
  z_str.clear();
  z_str = z_str.setNum(vec3d.z());

  QString result = x_str + "," + y_str+","+z_str;
  return result;
}

QString QVector2DToString(QVector2D vec2d) {
  QString x_str ;
  x_str.clear();
  x_str = x_str.setNum(vec2d.x());

  QString y_str;
  y_str.clear();
  y_str = y_str.setNum(vec2d.y());

  QString result = x_str + "," + y_str;

  return result;
}

QString PointFToString(QPointF point) {
  QString x_str;
  x_str.clear();
  x_str = x_str.setNum(point.x());

  QString y_str;
  y_str.clear();
  y_str = y_str.setNum(point.y());

  QString result = x_str + "," + y_str;

  return result;
}