#ifndef MANGO_2D_JSON_UTIL_H_
#define MANGO_2D_JSON_UTIL_H_
#include <QJsonObject>
#include <QPointF>
#include <QVector3D>
#include <QVector2D>
void AttachJsonObject(QJsonObject& obj1, QJsonObject& obj2);

QString PointFToString(QPointF point);

QString QVector3DToString(QVector3D vec3d);

QString QVector2DToString(QVector2D vec2d);
#endif
