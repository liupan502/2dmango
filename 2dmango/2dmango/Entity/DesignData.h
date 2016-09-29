//#ifndef MANGO_2D_DESIGN_DATA_H_
#ifndef MANGO_2D_DESIGN_DATA_H_
#define MANGO_2D_DESIGN_DATA_H_

#include "BaseData.h"
#include "WallData.h"
#include "CornerData.h"
#include "RoomData.h"

#include "Geometry/WallGeometry.h"
#include <QVector2d>

#include <vector>
#include <map>
#include <set>
//const int MAX_WALL_NUM = 10000;
//const int MAX_CORNER_NUM = 10000;
//const int MAX_ROOM_NUM = 1000;

class DesignData :public BaseData {
  public:
    virtual std::string ToJson();

    WallData* AddWall();
    CornerData* AddCorner();
    RoomData* AddRoom();
    std::vector<WallGeometry> ComputeWallGeometrys();

    bool FindConnectedPoints(QPointF currentPoint, std::string wallName,std::vector<QPointF>& points);

    bool FindAttachedCorner(QPointF currentPoint, std::string wallName, std::vector<CornerData*>& cornerNames);

    QPointF CornerPosition(std::string cornerName);

    void UpdateRoomInfo();

	void UpdateGeometry();

  private:

    void clear_rooms();

    //bool is_connected_point(QPointF currentPoint,QVector2D vec ,QPointF testPoint);
    bool is_connected_corner(CornerData);

    QPointF compute_connected_point(WallData* wall, CornerData* corner);

    bool is_valid_connected_point(std::string pointName,std::string wallName, std::set<std::string>cornersSet);

    bool is_attached_corner(QPointF currentPoint,std::string wallName,std::string cornerName, std::set<std::string> cornersName);

    

    void reset_geometry();

    void update_wall_geometrys();

    void update_wall_geometry(WallData* wall);

    void update_corner_positions();

    void update_corner_position(CornerData* corner);

    std::vector<WallData*> find_wall_with_corner_name(std::string cornerName);
    
    std::string generte_wall_name();

    std::string generate_corner_name();

    std::string generate_room_name();

    std::string generate_line_name();

    std::string generate_point_name();

    std::string generate_name(std::vector<std::string> used_names);

    void compute_corner_position(std::string corner_name);

    void sort_wall(std::vector<WallData*>& wall_datas);

    void find_unclosed_walls(std::set<WallData*>& unclosedWalls);

    void update_exclude_walls(std::set<WallData*>& exclude_walls, std::vector<WallData*>walls);

    RoomData* find_available_room(std::set<RoomData*> excludeRooms,std::set<WallData*> excludeWalls);

    

    
    // ǽ������
    std::map<std::string,WallData*> wall_data_map_;

    // corner ����
    std::map<std::string,CornerData*> corner_data_map_;

    // ��������
    std::map<std::string,RoomData*> room_data_map_;
};
#endif // !MANGO_2D_DESIGN_DATA_H_

