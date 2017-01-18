#pragma once
#include "ModelSelectItemDelegate.h"

ModelSelectedItemDelegate::ModelSelectedItemDelegate(QObject* parent)
                           :QAbstractItemDelegate(parent){
}

void ModelSelectedItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,
  const QModelIndex& index) const {

  painter->setRenderHint(QPainter::Antialiasing);
  painter->setRenderHint(QPainter::SmoothPixmapTransform);
  
  if (option.state & QStyle::State_Selected) {
    painter->fillRect(option.rect, option.palette.highlight());
  }
  

  int offset = 4;
  int size = qMin(option.rect.width(), option.rect.height());
  QPoint rect_center = option.rect.center();//(option.rect.width() / 2.0+option.rect., option.rect.height() / 2.0);
  QPoint top_left_point = rect_center - QPoint(size / 2.0- offset, size / 2.0- offset);
  QRect rect(top_left_point, QSize(size-2*offset, size-2*offset));
  QImage img = index.model()->data(index, Qt::DecorationRole).value<QImage>();
  int img_size = qMin(img.width(), img.height());
  QRect src_rect(0, 0, img_size, img_size);

  painter->save();
  painter->setRenderHint(QPainter::Antialiasing, true);
  painter->setPen(Qt::NoPen);

  if (option.state&QStyle::State_Selected) {
    painter->setBrush(option.palette.highlightedText());
  }
  else {
    painter->setBrush(option.palette.text());
  }
  painter->drawImage(rect, img, src_rect);
  painter->restore();
}

QSize ModelSelectedItemDelegate::sizeHint(const QStyleOptionViewItem & option,
  const QModelIndex &index) const {
  return QSize(100, 100);
}