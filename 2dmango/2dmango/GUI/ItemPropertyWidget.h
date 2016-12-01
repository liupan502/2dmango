#pragma once
#include <QSpinBox>
#include <QWidget>
#include "Entity\BaseData.h"



class BaseItemPropertyDetailWidget : public QWidget {
  Q_OBJECT
public:
  BaseItemPropertyDetailWidget(QWidget * parent = Q_NULLPTR);
  virtual ~BaseItemPropertyDetailWidget();
  virtual void set_data(BaseGeometryData* data) {} ;
  virtual void UpdateContent(bool isViewToData) {} ;
  void init();
protected:
  BaseGeometryData* data_;
  
};

class ModelPropertyDetailWidget :public BaseItemPropertyDetailWidget {
  Q_OBJECT
public:
  ModelPropertyDetailWidget(QWidget * parent = Q_NULLPTR);
  virtual ~ModelPropertyDetailWidget();
  virtual void set_data(BaseGeometryData* data);
  virtual void UpdateContent(bool isViewToData);

  protected slots:
  void OnOffsetZChanged(int value);
  void OnRotationChanged(int value);

protected:
  void init();
  QSpinBox* spin_box_offset_z_;
  QSpinBox* spin_box_rotation_;
};

class OpeningPropertyDetailWidget :public BaseItemPropertyDetailWidget {
  Q_OBJECT
public:
  OpeningPropertyDetailWidget(QWidget * parent = Q_NULLPTR);
  virtual ~OpeningPropertyDetailWidget();
  virtual void set_data(BaseGeometryData* data);
  virtual void UpdateContent(bool isViewToData);
  protected slots:
    void OnOffsetZChanged(int value);
    void OnLengthChanged(int value);
    void OnWidthChanged(int value);
protected:
  void init();
  QSpinBox* spin_box_offset_z_;
  QSpinBox* spin_box_length_;
  QSpinBox* spin_box_width_;
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
  void init(QWidget * parent);
};