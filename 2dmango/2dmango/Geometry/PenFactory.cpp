#include "PenFactory.h"

QPen PenFactory::pen1() {
  return QPen(Qt::black, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
}