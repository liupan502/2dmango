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
  ArcPath(QPointF p1, QPointF p2,float radius);
  void set_p1(QPointF p1);
  void set_p2(QPointF p2);
  void set_radius(float radius);
private:
  QPointF p1_;
  QPointF p2_;
  float radius_;
};

class ContianerPath :public BasePath {
public:
  virtual QPainterPath GetPainterPath();
  void AddSubPath(BasePath* subPath);
private:
  std::vector<BasePath*> subPaths;
};


#endif 
