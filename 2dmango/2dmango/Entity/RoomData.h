#ifndef MANGO_2D_ROOM_DATA_H_
#define MANGO_2D_ROOM_DATA_H_

#include "BaseData.h"
#include <string>
#include <vector>
#include<set>

class WallData;
class CornerData;
class PointData;
class RoomData :public BaseData {
  public:

    RoomData();

    RoomData(std::string name,std::vector<WallData*> walls);

    void set_func_name(std::string func_name){
      func_name_ = func_name;
    }

    std::string func_name(){
      return func_name_;
    }

    void set_wall_names(std::vector<std::string> wall_names){
      wall_names_ = wall_names;
    }

    std::vector<std::string> wall_names(){
      return wall_names_;
    }

    void set_corner_names(std::vector<std::string> corner_names){
      corner_names_ = corner_names;
    }

    void set_extra_wall_names(std::vector<std::string> wall_names){
      extra_wall_names_ = wall_names;
    }

    std::vector<std::string> extra_wall_names(){
      return extra_wall_names_;
    }

    void set_extra_corner_names(std::vector<std::string> corner_names){
      extra_corner_names_ = corner_names;
    }

    std::vector<std::string> extra_corner_names() {
      return extra_corner_names_;
    }

    bool CanComputeWallGeometry(std::set<WallData*>excludeWalls);

    std::vector<WallData*> walls();

    void GenerateLines();

    std::string virtual ToJson();
  private:
    std::string func_name_;

    // 按照逆时针顺序的构成房间轮廓的墙名字
    std::vector<std::string> wall_names_;

    // 房间内部的墙
    std::vector<std::string> extra_wall_names_;

    // 按照逆时针顺序构成的房间轮廓的corner 的名字
    std::vector<std::string> corner_names_;

    // 房间内部的corner
    std::vector<std::string> extra_corner_names_;

    std::vector<WallData*> walls_;

    CornerData* find_previous_corner(int current_index);    

    bool check_wall(CornerData* previousCorner,int currentIndex,std::set<WallData*> excludeWalls);

    std::vector<PointData*> polygon();

    
};

#endif // !MANGO_2D_ROOM_DATA_H_

