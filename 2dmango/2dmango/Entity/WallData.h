#ifndef MANGO_2D_WALL_DATA_H_
#define MANGO_2D_WALL_DATA_H_
/*
author:  Liu pan  
version: 1.0.0
date:    2016.9.15
*/


#include "BaseData.h"

#include "LineData.h"

#include <string>
#include <set>

#include <QVector2D>
#include "Geometry/WallGeometry.h"
#include "PointData.h"
#include "const.h"

typedef enum WALL_DATA_TYPE {

  // 存储数据为内墙线的数据
  WALL_INSIDE_DATA,

  // 存储的数据为墙中线数据
  WALL_MIDDLE_DATA,

  // 存储的数据为外墙线数据
  WALL_OUTSIDE_DATA,
} WALL_DATA_TYPE;

typedef enum WALL_DATA_STATUS {	
	NONE_STAUS_WALL_DATA,
	DRAWING_WALL_DATA,
	UNROOM_WALL_DATA,
	ROOM_WALL_DATA,
} WALL_DATA_STATUS;

class CornerData;
class RoomData;

class WallData :public BaseGeometryData{
  public:
    WallData(){     
     generated_line_.set_is_independent(false);
     start_corner_ = NULL;
     end_corner_ = NULL;
     normal_vector_ = QVector2D();
     set_width(DEFAULT_WALL_WIDTH);
	   status_ = NONE_STAUS_WALL_DATA;
   }

	void set_status(WALL_DATA_STATUS status);

	WALL_DATA_STATUS status();

    bool DoContainCorner(CornerData* corner);

    bool IsStartCorner(CornerData* corner);
    
    bool IsEndCorner(CornerData* corner);

    bool IsUnsharedWall(std::set<WallData*> excludeWalls);

    bool IsInsideConnected(WallData* wall);

	/*
	  void set_start_corner_name(std::string name){
      start_corner_name_ = name;
      own_start_corner_data_ = true;
    } 
	*/
    void ResetGeometry();

    WallGeometry GetGeometry();
    
    //RoomData* GetRoom(std::set<WallData*> excludeWalls);

    std::vector<WallData*> GetRoom(std::set<WallData*> excludeWalls,std::vector<WallData*> currentPath = std::vector<WallData*>());

    std::string start_corner_name();
    /*{
      return start_corner_name_;
    }*/

    std::vector<std::string> AllLineNames();

    QVector2D WallVector();

    QVector2D WallPerpendicularVector();

    void set_normal_vector(QVector2D vector);

    QVector2D normal_vector();

    QLineF WallLine();

    LineData line();

    LineData generate_line();

    PointData*  GetConnectedPoint(WallData* wall);

    CornerData* GetConnectedCorner(WallData* wall);

    void set_line_start_name(std::string name);
    void set_line_end_name(std::string name);
    void set_generated_line_start_name(std::string name);
    void set_generated_line_end_name(std::string name);

    void UpdateLine();
    void UpdateGeneratedLine();


	/*
    void set_end_corner_name(std::string name){
      end_corner_name_ = name;
      own_end_corner_data_ = true;
    }*/

    std::string end_corner_name();
    /*{
      return end_corner_name_;
    }*/
    
	/*
    void set_own_start_corner_data(bool bown){
      own_start_corner_data_ = bown;
    }
    
    bool own_start_corner_data(){
      return own_start_corner_data_;
    }

    
    void set_own_end_corner_data(bool bown){
      own_end_corner_data_ = bown;
    }

    bool own_end_corner_data(){
      return own_end_corner_data_;
    }*/

    void set_start_corner_position(QPointF position);
    /*{
      //start_corner_position_ = position;
    
    }*/

    
    QPointF start_corner_position();
    /*{
      return start_corner_position_;
    }*/

    void set_end_corner_position(QPointF position);
    /*{
      end_corner_position_ = position;
    }*/

    
    QPointF end_corner_position();
    /*{
      return end_corner_position_;
    }*/

    /*void set_is_completed(bool isCompleted){
      is_completed_ = isCompleted;
    }*/

    /*bool is_completed(){
      return is_completed_;
    }  */  

    void set_start_corner(CornerData* corner);

    CornerData* start_corner();

    void set_end_corner(CornerData* corner);

    CornerData* end_corner();

    void ComputePoint(PointData* point);

    bool DoContianPoint(PointData* point);

    LineData GetLine(PointData* point);

	//LineData generated_line();

	void UpdateGeneratedLine(LineData line);

    virtual std::string ToJson();
  private:
    
    bool is_available_path(std::vector<WallData*> wallPath);

    bool is_room_path(std::vector<WallData*> wallPath);

    CornerData* find_last_corner(std::vector<WallData*> wallPath);

    PointData* start_start_connected_position(WallData* startCornerWall,CornerData* corner);

    PointData* start_end_connected_position(WallData* endCornerWall, CornerData* corner);

    PointData* end_start_connected_position(WallData* startCornerWall, CornerData* corner);

    PointData* end_end_connected_position(WallData* endCornerWall, CornerData* corner);

    PointData* compute_connected_position(CornerData* corner,WallData* wall,std::string name1,std::string generateName1,
                                                                               std::string name2,std::string generateName2);

	int compare_wall_path(std::vector<WallData*> path1, std::vector <WallData*> path2);

    // 按照逆时针方向的第一个点
    //std::string start_corner_name_;

    // 按照逆时针方向的第二个点
    //std::string end_corner_name_;
    
    // 墙的位置数据解析方式（墙中线 or 内墙线 or 外墙线） 
    WALL_DATA_TYPE data_type_;

    // 墙是否拥有开始点的数据，如果没有则说明开始点是通过corner计算出来的
    //bool own_start_corner_data_;

    // 墙是否拥有结束点的数据，如果没有则说明结束点是通过corner计算出来的
    //bool own_end_corner_data_;

    //bool is_completed_;
	WALL_DATA_STATUS status_;
    //QPointF start_corner_position_;
    //QPointF end_corner_position_;
    LineData line_;
    LineData generated_line_;
    CornerData* start_corner_;
    CornerData* end_corner_;
    QVector2D normal_vector_;
};

#endif

