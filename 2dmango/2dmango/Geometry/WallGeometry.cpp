#include "WallGeometry.h"
WallGeometry::WallGeometry():BaseGeometry() {
  
}

WallGeometry::WallGeometry(QPolygonF polygon) {
  polygon_ = polygon;
}

WallGeometry::WallGeometry(std::vector<QPointF> points) {
  int size = points.size();
  if(size == 2){
    LinesPath* lines_path = new LinesPath(points);
    lines_path->set_pen(QPen(Qt::green, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
    paths_.push_back((BasePath*)lines_path);
  }

  if (size == 6) {
	  QPolygonF polygon;
	  for (int i = 0; i <= size; i++) {
		  int index = i%size;
		  QPointF point = points[index];
		  polygon << point;
	  }
	  PolygonPath* polygon_path = new PolygonPath(polygon);
	  polygon_path->set_pen(QPen(Qt::black, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
	  polygon_path->set_brush(QBrush(Qt::yellow));
	  paths_.push_back(polygon_path);
  }
}