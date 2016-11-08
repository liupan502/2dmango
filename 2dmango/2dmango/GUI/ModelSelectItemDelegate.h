#pragma once
#include <QAbstractItemDelegate>
#include <QPainter>
class ModelSelectedItemDelegate :public QAbstractItemDelegate {
  Q_OBJECT
public:
  ModelSelectedItemDelegate(QObject* parent = 0);
  void paint(QPainter* painter, const QStyleOptionViewItem&option,
    const QModelIndex& index) const Q_DECL_OVERRIDE;
  QSize sizeHint(const QStyleOptionViewItem & option,
    const QModelIndex &index) const Q_DECL_OVERRIDE;

  
};