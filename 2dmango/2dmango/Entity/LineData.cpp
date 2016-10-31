#include "LineData.h"
#include "Util/LineUtil.h"
#include <assert.h>
LineData::LineData():BaseData() {
  is_independent_ = true;
  start_point_name_ = "";
  end_point_name_ = "";
}

LineData::LineData(std::string lineName, std::string startPointName, std::string endPointName, bool isIndependent) :BaseData(lineName) {
  start_point_name_ = startPointName;
  end_point_name_ = endPointName;
  is_independent_ = isIndependent;
}

void LineData::set_start_point_name(std::string name) {
  start_point_name_ = name;
}

std::string LineData::start_point_name() {
  return start_point_name_;
}

void LineData::set_end_point_name(std::string name) {
  end_point_name_ = name;
}

std::string LineData::end_point_name() {
  return end_point_name_;
}

void LineData::set_is_independent(bool isIndependent) {
  is_independent_ = isIndependent;
}

bool LineData::is_independent() {
  return is_independent_;
}

QJsonObject LineData::ToJson() {
  QJsonObject object;
  QJsonObject parent_object = BaseData::ToJson();
  AttachJsonObject(object, parent_object);
  object.insert("start_point_name", QJsonValue(start_point_name_.c_str()));
  object.insert("end_point_name", QJsonValue(end_point_name_.c_str()));
  object.insert("is_independent", QJsonValue(is_independent_));
  QPointF start_point = line_.p1();
  QString start_point_position_str = PointFToString(start_point);
  object.insert("start_point_position", QJsonValue(start_point_position_str));
  QPointF end_point = line_.p2();
  QString end_point_position_str = PointFToString(end_point);
  object.insert("end_point_position", QJsonValue(end_point_position_str));
  return object;
}

void LineData::InitWithObject(QJsonObject& jsonObject) {
  BaseData::InitWithObject(jsonObject);
  if (jsonObject.contains("start_point_name")) {
    start_point_name_ = jsonObject["start_point_name"].toString().toStdString();
  }
  else {
    start_point_name_ = "";
  }

  if (jsonObject.contains("end_point_name")) {
    end_point_name_ = jsonObject["end_point_name"].toString().toStdString();
  }
  else {
    end_point_name_ = "";
  }

  if (jsonObject.contains("is_independent")) {
    is_independent_ = jsonObject["is_independent"].toBool();
  }
  else {
    is_independent_ = false;
  }

  QPointF start_point;
  if (jsonObject.contains("start_point_position")) {
    QString start_point_str = jsonObject["start_point_position"].toString();
    start_point = StringToPointF(start_point_str);
  }

  QPointF end_point;
  if (jsonObject.contains("end_point_position")) {
    QString end_point_str = jsonObject["end_point_position"].toString();
    end_point = StringToPointF(end_point_str);
  }

  line_ = QLineF(start_point, end_point);
}

std::string LineData::find_connected_point(LineData line) {
  std::string connected_point_name = "";
  if (DoCotainPoint(line.start_point_name())) {
    connected_point_name = line.start_point_name();
  }
  else if (DoCotainPoint(line.end_point_name())) {
    connected_point_name = line.end_point_name();
  }
  return connected_point_name; 
}

bool LineData::IsStartPoint(std::string pointName) {
  return (start_point_name() == pointName);
}

bool LineData::IsEndPoint(std::string pointName){
  return (end_point_name() == pointName);
}

bool LineData::DoCotainPoint(std::string pointName) {
  return ((IsStartPoint(pointName))||(IsEndPoint(pointName)));
}



void LineData::Reset() {
  line_ = QLineF();
}

QLineF LineData::Line() {
 
  return line_;
}

void LineData::set_line(QLineF line) {
  line_ = line;
}

QPointF LineData::Intersect(LineData lineData) {
  QLineF line = Line();
  QLineF other_line = lineData.Line();
  QPointF intersect_point;
  if (IsSameLine(line, other_line)) {
    return GetSameLinesConnectedPoint(line, other_line);
  }
  else if (line.intersect(other_line, &intersect_point) != QLineF::NoIntersection) {
    return intersect_point;
  }  
  else {
    assert(false);
    return QPointF();
  }
}

bool LineData::IsAvailable() {
  return (!line_.isNull());
}