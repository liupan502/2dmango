#ifndef  MANGO_2D_CORNER_DATA_H_
#define  MANGO_2D_CORNER_DATA_H_
/*
author:  Liu pan
version: 1.0.0
date:    2016.9.15
*/

#include "BaseData.h"
#include <string>
#include "PointData.h"
#include <map>
#include <set>

class WallData;

class CornerData :public BaseGeometryData{
  public:
    CornerData();    
    virtual ~CornerData();
    virtual std::string ToJson();
    std::string AddPoint(QPointF point);
    void RemovePoint(std::string pointName);
    void UpdatePoint(std::string pointName,QPointF point);
    PointData*  GetPoint(std::string pointName);
    
    std::string GetPointName(QPointF point);

    void set_position(QVector3D position);
    bool has_position_data();
    std::vector<std::string> AllPointNames();
    void AddRelatedWall(WallData* wall);
    void RemoveRelatedWall(WallData* wall);
    void GetUnclosedWalls(std::set<WallData*>& unclosedWalls,WallData* exclude_wall = NULL);
    int RelateWallSize(std::set<WallData*> excludeWalls = std::set<WallData*>());
    std::vector<WallData*> RelateWalls();
    bool DoContainPoint(PointData* point);
    void UpdateCornerPosition();
    std::vector<CornerData*> FindPathTo(CornerData* corner, std::vector<CornerData> previousPath);
    std::vector<CornerData*> NextCorners();
    
  private:
	  void update_wall_generated_line_info(WallData* wall, std::string point_name);

    bool has_position_data_;
    std::map<std::string,PointData*> point_data_map_;
    std::map<std::string,WallData*> related_wall_map_;
    std::string generate_point_name();

};

#endif // ! MANGO_2D_CORNER_DATA_H_

