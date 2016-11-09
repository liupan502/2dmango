#include "DesignDataWrapper.h"

void DesignDataWrapper::ShowHotRegion(bool is_visible) {
  hot_region_->set_is_visible(is_visible);
}

void DesignDataWrapper::HotRegionMoveTo(QPointF position) {
  hot_region_->MoveTo(position);
}

bool DesignDataWrapper::IsPointInHotRegion(QPointF point) {
  return hot_region_->ContainsPoint(point);
}