#ifndef MANGO_2D_DRAW_WALL_MOUSE_ADAPTER_H_
#define MANGO_2D_DRAW_WALL_MOUSE_ADAPTER_H_

#include "BaseActionAdapter.h"
#include "Entity/WallData.h"
#include "Entity/DesignDataWrapper.h"
class  DrawWallActionAdapter : public BaseActionAdapter {
  public:

    DrawWallActionAdapter();
    virtual void OnMouseMove(QMouseEvent* event);

    virtual void OnMousePress(QMouseEvent* event);

    virtual void OnMouseRelease(QMouseEvent* event);

    Q_OBJECT
    signals:
    void EndDrawWall();

  private:
    
    void left_mouse_button_press(QMouseEvent* event);
    void left_mouse_button_release(QMouseEvent* event);
    void right_mouse_button_release(QMouseEvent* event);

    void ready_mouse_move(QMouseEvent* event);
    void initilizing_mouse_move(QMouseEvent* event);
    void drawing_mouse_move(QMouseEvent* event);

    void ready_left_mouse_press(QMouseEvent* event);
    void initilizing_left_mouse_press(QMouseEvent* event);
    void drawing_left_mouse_press(QMouseEvent* event);

    void ready_left_mouse_release(QMouseEvent* event);
    void initilizing_left_mouse_release(QMouseEvent* event);
    void drawing_left_mouse_release(QMouseEvent* event);

    void current_room_complete(std::string cornerName);

    QPointF compute_right_position(WallData* wall,QPointF position );
    QPointF compute_connected_position(WallData* wall,QPointF connectPoint);
    
    CornerData* previous_corner_;
    CornerData* current_corner_;

    QPointF previous_point_;
    QPointF current_point_;

    //QPointF 

    bool left_mouse_down_;
    bool bdrawing_;
    bool is_fixed_;
	
    bool is_current_room_completed_;
    WallData* tmp_wall_;   
    int draw_status_;

    QPointF start_point_;
    bool is_first_room_;
};
#endif
