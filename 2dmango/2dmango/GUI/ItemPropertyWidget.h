#pragma once

#include <QWidget>
#include "Entity\BaseData.h"


class BaseItemPropertyDetailWidget : public QWidget {
  Q_OBJECT
public:
  BaseItemPropertyDetailWidget(QWidget * parent = Q_NULLPTR);
  ~BaseItemPropertyDetailWidget();
  virtual void set_data(BaseGeometryData* data) = 0;
  virtual void UpdateContent(bool isViewToData) = 0;

protected:
  BaseGeometryData* data_;
};

class ModelPropertyDetailWidget :public BaseItemPropertyDetailWidget {
  Q_OBJECT
public:
  ModelPropertyDetailWidget(QWidget * parent = Q_NULLPTR);
  ~ModelPropertyDetailWidget();
  virtual void set_data(BaseGeometryData* data);
  virtual void UpdateContent(bool isViewToData);
};

class OpeningPropertyDetailWidget :public BaseItemPropertyDetailWidget {
  Q_OBJECT
public:
  OpeningPropertyDetailWidget(QWidget * parent = Q_NULLPTR);
  ~OpeningPropertyDetailWidget();
  virtual void set_data(BaseGeometryData* data);
  virtual void UpdateContent(bool isViewToData);
};



class ItemPropertyWidget :public QWidget {
  Q_OBJECT

public:
  ItemPropertyWidget(QWidget * parent = Q_NULLPTR);
  ~ItemPropertyWidget();
  void SetGetmetryData(BaseGeometryData* data);

protected:  
  BaseItemPropertyDetailWidget* detail_widget_;
  ModelPropertyDetailWidget* model_detail_widget_;
  OpeningPropertyDetailWidget* opening_detail_widget_;
};