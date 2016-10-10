#ifndef MANGO_2D_DESIGN_DATA_WRAPPER_H_
#define MANGO_2D_DESIGN_DATA_WRAPPER_H_

#include "DesignData.h"
#include "CornerData.h"
#include "WallData.h"
#include "RoomData.h"
#include <QPainter>
#include "Geometry/HotRegionGeometry.h"
#include "Geometry/AuxiliaryLineGeometry.h"

#include <string>
#include <vector>

class DesignDataWrapper {

  public:
    
    virtual ~DesignDataWrapper()
    {
      delete_current_selected_geometry();
    }
    void Draw(QPainter* painter);
    WallData* AddWall();

    CornerData* AddCorner();
    std::string AddWall(std::string cornerName1,std::string cornerName2);
    std::string AddRoom(std::vector<std::string> cornerNames);

    void UpdateGeometry();

    void ShowHotRegion(bool is_visible) ;

    void HotRegionMoveTo(QPointF postion);

    bool IsPointInHotRegion(QPointF point);

    bool FindConnectedPoints(QPointF currentPoint,std::string wallName,std::vector<QPointF>& points);

    void AddAuxiliaryLine(QPointF point1,QPointF point2);

    void ClearAuxiliaryLines();

    bool FindAttachedCorner(QPointF currentPoint,std::string wallName, std::vector<CornerData*>& points);

    QPointF CornerPosition(std::string cornerName);

    bool FindStartPoint(QPointF currentPoint, QPointF& startPoint);

    CornerData* FindCornerWithPosition(QPointF currentPosition);

    bool FindEndPoint(WallData* wall_data, CornerData* corner, QPointF currentPoint, QPointF& endPoint);

    bool IsEmpty();

    void UpdateRoomInfo();

    void AddGeometry(BaseGeometry* selected);

    void AddCurrentData();

    BaseGeometry* current_selected_geometry();

    bool GetClosestWall(QPointF position,qreal& distance,WallGeometry& wallGeometry);

    static DesignDataWrapper* GetInstance();
    
  private:

   DesignDataWrapper();
   //void DrawWall(QPainter* painter);
   
   
   static DesignDataWrapper *instance ;
   static const int cost = 0;
   DesignData* design_data_;
   std::vector<WallGeometry> wall_geometrys_;
   HotRegionGeometry hot_region_;

   std::vector<AuxiliaryLineGeometry> auxiliary_lines_;

   BaseGeometry* current_selected_geometry_;

   void delete_current_selected_geometry();
   
   void insert_opening_data(InnerWallGeometry* innerWallGeometry);

   WallData* FindWallWithInnerWallGeometry(InnerWallGeometry* innerWallGeometry);


};


#endif
