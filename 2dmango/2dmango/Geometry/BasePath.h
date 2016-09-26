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


#endif 
