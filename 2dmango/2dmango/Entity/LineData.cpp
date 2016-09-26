#include "LineData.h"
#include "Util/LineUtil.h"
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

std::string LineData::ToJson() {
  return "";
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
  if (line.intersect(other_line, &intersect_point) != QLineF::NoIntersection) {
    return intersect_point;
  }
  else if (IsSameLine(line, other_line)) {
    return GetSameLinesConnectedPoint(line, other_line);
  }
  else {
    return QPointF();
  }
}