#ifndef MANGO_2D_BASE_PAINTER_PATH_H_
#define MANGO_2D_BASE_PAINTER_PATH_H_
#include <QPainterPath>
#include <vector>
#include <QPen>

class BasePath {
  public:
    virtual QPainterPath GetPainterPath();

    QPen pen();
    void set_pen(QPen pen);
    QBrush brush();
    void set_brush(QBrush brush);


    void AddSubPath(BasePath* subPath);

    virtual ~BasePath();

  protected:
    std::vector<BasePath*> sub_paths_;
    
    QPen pen_;
    QBrush brush_;
  private:
       
};

class LinesPath: public BasePath {
  public:
    virtual QPainterPath GetPainterPath();
    LinesPath(std::vector<QPointF> points);
    void set_points(std::vector<QPointF> points);
    
  private:    
    std::vector<QPointF> points_;
};

class PolygonPath :public BasePath{
  public:
    virtual QPainterPath GetPainterPath();
    PolygonPath(QPolygonF polygon);
    void set_polygon(QPolygonF polygon);
  private:
    QPolygonF polygon_;
};

class EllipsePath :public BasePath{
  public:
    virtual QPainterPath GetPainterPath();
    EllipsePath(QPointF center,qreal rx,qreal ry);
    void set_center(QPointF center);
    void set_rx(qreal rx);
    void set_ry(qreal ry);

  private:
    QPointF center_;
    qreal rx_,ry_; 
};

class ArcPath :public BasePath {
public:
  virtual QPainterPath GetPainterPath();
  ArcPath(QRectF rect,qreal startAngle,qreal sweepLength, QPointF start_point);
  void set_rect(QRectF rect);
  void set_start_angle(qreal startAngle);
  void set_sweep_length(qreal sweepLength);
  
  void Update(QRectF rect, qreal startAngle, qreal sweepLength,QPointF start_point);
private:
  QRectF rect_;
  qreal start_angle_;
  qreal sweep_length_;
  QPointF start_point_;
};

class ContianerPath :public BasePath {
public:
  virtual QPainterPath GetPainterPath();
  void AddSubPath(BasePath* subPath);
  virtual ~ContianerPath();
 
private:
  std::vector<BasePath*> sub_paths_;
};


#endif 
