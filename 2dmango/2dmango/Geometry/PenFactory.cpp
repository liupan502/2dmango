#include "PenFactory.h"

QPen PenFactory::pen1() {
  return QPen(QColor("#6b6b6b"), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
}