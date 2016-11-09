#ifndef MANGO_2D_AUXILIARY_LINE_GEOMETRY_H_
#define MANGO_2D_AUXILIARY_LINE_GEOMETRY_H_
#include "BaseGeometry.h"

class AuxiliaryLineGeometry :public BaseGeometry {
  public:
    AuxiliaryLineGeometry();
    AuxiliaryLineGeometry(const AuxiliaryLineGeometry& value);
    ~AuxiliaryLineGeometry();
    AuxiliaryLineGeometry(QPointF point1,QPointF point2);
    void SetLineGeometry(QPointF point1, QPointF point2);

  private:
    QPointF point1_,point2_;
};
#endif // !MANGO_2D_AUXILIARY_LINE_GEOMETRY_H_

