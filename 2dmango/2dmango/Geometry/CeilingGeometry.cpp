#include "CeilingGeometry.h"
#include "Entity/RoomData.h"
#include "Util/PolygonUtil.h"

CeilingGeometry::CeilingGeometry(BaseCeilingData* ceilingData,RoomData* roomData):BaseGeometry((BaseGeometryData*)ceilingData) {

  //std::vector<QVector2D> polygon;
  if (!roomData) {
    polygon_ = default_polygon();
  }
  else {
    polygon_ = roomData->InnerWallPoints();
  } 

  build_geometry();
}

CeilingGeometry::~CeilingGeometry() {
  
}

void CeilingGeometry::build_geometry() {
  if (polygon_.size() < 3)
    return;
  for (int i = 0; i < paths_.size(); i++) {
    delete paths_[i];
    paths_[i] = NULL;
  }
  paths_.clear();

  float ceiling_width = data_->is_tmp_data() ? 40 : data_->width();
  //float ceiling_width = data_->is_tmp_data() ? 40 : 40;
  bool is_counterclockwise = IsCounterclockwisePolygon(polygon_);
  for (int i = 0; i < polygon_.size(); i++) {
    int index1 = i;
    int index2 = (i + 1) % polygon_.size();
    int index3 = (i + 2) % polygon_.size();
    int index4 = (i + 3) % polygon_.size();
    QPointF point1 = polygon_[index1];
    QPointF point2 = polygon_[index2];
    QPointF point3 = polygon_[index3];
    QPointF point4 = polygon_[index4];
    QVector2D direction1 = QVector2D(point2 - point1);
    QVector2D normal_direction1 = is_counterclockwise ? QVector2D(-direction1.y(), direction1.x()) : QVector2D(direction1.y(), -direction1.x());
    normal_direction1.normalize();
    direction1.normalize();

    QVector2D direction2 = QVector2D(point3 - point2);
    QVector2D normal_direction2 = is_counterclockwise ? QVector2D(-direction2.y(), direction2.x()) : QVector2D(direction2.y(), -direction2.x());
    normal_direction2.normalize();
    direction2.normalize();

    QVector2D direction3 = QVector2D(point4 - point3);
    QVector2D normal_direction3 = is_counterclockwise ? QVector2D(-direction3.y(), direction3.x()) : QVector2D(direction3.y(), -direction3.x());
    normal_direction3.normalize();
    direction3.normalize();

    float val1 = -QVector2D::dotProduct(direction1, direction2);
    float radian1 = acos(val1) / 2.0;
    float length1 = ceiling_width / tan(radian1);
    QVector2D offset1 = -direction1*length1 + normal_direction1*ceiling_width;

    float val2 = -QVector2D::dotProduct(direction2, direction3);
    float radian2 = acos(val2) / 2.0;
    float length2 = ceiling_width / tan(radian2);
    QVector2D offset2 = -direction2*length2 + normal_direction2*ceiling_width;

    QPolygonF polygon;
    polygon << point2 << point3 << point3 + QPointF(offset2.x(), offset2.y()) << point2 + QPointF(offset1.x(), offset1.y());
    PolygonPath* polygon_path = new PolygonPath(polygon);
    polygon_path->set_brush(QBrush(QColor(255, 123, 0, 50)));
    paths_.push_back(polygon_path);

  }
}

std::vector<QPointF> CeilingGeometry::default_polygon(QPointF offset) {
  std::vector<QPointF> result;
  result.push_back(QPointF(-100.0, -100.0)+offset);
  result.push_back(QPointF(100.0, -100.0) + offset);
  result.push_back(QPointF(100, 100) + offset);
  result.push_back(QPointF(-100, 100) + offset);
  return result;
}