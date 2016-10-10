#include "WallGeometry.h"
#include "Entity/WallData.h"
#include <assert.h>
#include "Util/LineUtil.h"

WallGeometry::WallGeometry():BaseGeometry() {
  geometry_type_ = GEOMETRY_WALL;
}

WallGeometry::WallGeometry(QPolygonF polygon) {
  polygon_ = polygon;
  geometry_type_ = GEOMETRY_WALL;
}

WallGeometry::WallGeometry(std::vector<QPointF> points,WallData* wallData) {
  wall_data_ = wallData;
  int size = points.size();
  if(size == 2){
    LinesPath* lines_path = new LinesPath(points);
    lines_path->set_pen(QPen(Qt::green, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
    paths_.push_back((BasePath*)lines_path);
  }

  if (size == 6) {
	  //QPolygonF polygon;
    polygon_.clear();
	  for (int i = 0; i <= size; i++) {
		  int index = i%size;
		  QPointF point = points[index];
      polygon_ << point;
	  }
	  PolygonPath* polygon_path = new PolygonPath(polygon_);
	  polygon_path->set_pen(QPen(Qt::black, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
	  polygon_path->set_brush(QBrush(Qt::yellow));
	  paths_.push_back(polygon_path);
  }

  geometry_type_ = GEOMETRY_WALL;
}

bool WallGeometry::PointDistanceToGeometry(QPointF position, qreal& distance) {
  assert(wall_data_->status() != DRAWING_WALL_DATA);
  if (polygon_.containsPoint(position, Qt::OddEvenFill)) {
    distance = 0;
    return true;
  }
  QLineF line1 = Line1();
  qreal distance1;
  int status1 = PointDistanceToLine(position,line1,distance1);
  QLineF line2 = Line2();
  qreal distance2;
  int status2 = PointDistanceToLine(position, line2, distance2);
  if (status1 == 0 && status2 == 0) {
    return false;
  }
  if (status1 == 1 && status2 == 1) {
    distance = distance1 < distance2 ? distance1 : distance2;
  }
  else if (status1 == 1) {
    distance = distance1;
  }
  else {
    distance = distance2;
  }
  return true;
}

QLineF WallGeometry::Line1() {
  return QLineF(polygon_[0], polygon_[5]);
}

QLineF WallGeometry::Line2() {
  return QLineF(polygon_[2],polygon_[3]);
}

QVector2D WallGeometry::WallVector() {
  return wall_data_->WallVector();
}

QVector2D WallGeometry::NormalVector() {
  QVector2D result =  wall_data_->normal_vector();
  result.normalize();
  return result;
}