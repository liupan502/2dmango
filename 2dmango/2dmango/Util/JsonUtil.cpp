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

QVector3D StringToQVector3D(QString string) {
  QVector3D vec3d;
  QStringList sub_strs = string.split(",");
  if (sub_strs.size() == 3) {
    qreal x = sub_strs[0].toFloat();
    qreal y = sub_strs[1].toFloat();
    qreal z = sub_strs[2].toFloat();
    vec3d = QVector3D(x, y,z);
  }
  return vec3d;
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

QVector2D StringToQVector2D(QString string) {
  QVector2D vec2d;
  QStringList sub_strs = string.split(",");
  if (sub_strs.size() == 2) {
    qreal x = sub_strs[0].toFloat();
    qreal y = sub_strs[1].toFloat();    
    vec2d = QVector2D(x, y);
  }
  return vec2d;
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

QPointF StringToPointF(QString string) {
  QPointF point;
  QStringList sub_strs = string.split(",");
  if (sub_strs.size() == 2) {
    qreal x = sub_strs[0].toFloat();
    qreal y = sub_strs[1].toFloat();
    point = QPointF(x, y);
  }
  return point;
}