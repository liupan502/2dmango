#ifndef MANGO_2D_JSON_UTIL_H_
#define MANGO_2D_JSON_UTIL_H_
#include <QJsonObject>
#include <QPointF>
#include <QVector3D>
#include <QVector2D>
void AttachJsonObject(QJsonObject& obj1, QJsonObject& obj2);

QString PointFToString(QPointF point);

QPointF StringToPointF(QString string);

QString QVector3DToString(QVector3D vec3d);

QVector3D StringToQVector3D(QString string);

QString QVector2DToString(QVector2D vec2d);

QVector2D StringToQVector2D(QString string);
#endif
