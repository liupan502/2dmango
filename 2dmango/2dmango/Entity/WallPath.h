#ifndef MANGO_2D_WALL_PATH_H_
#define MANGO_2D_WALL_PATH_H_

#include "BaseData.h"
#include "WallData.h"
#include "CornerData.h"
class WallPath : public BaseData{

public:
  WallPath();
  CornerData* start_corner();
  bool IsStartCorner(CornerData* corner);
  bool IsEndCorner(CornerData* corner);
  bool DoContianCorner(CornerData* corner);
  CornerData* end_corner();
  WallPath(std::vector<WallData*> walls);
  bool DoContianWall(WallData* wall);
  bool IsUnshare(std::set<WallPath*> excludeWallPaths);
  WallPath GetRoom(std::set<WallPath*> excludeWallPaths);
  std::vector < WallData*> walls();
  //bool operator < (const WallPath& other) const;
  virtual std::string ToJson();
  private:
    std::vector<WallData*> walls_;
};

class WallPathFactory {
  public:
    static std::map<std::string, WallPath*> CreateWallPaths(std::map<std::string,WallData*> wall_data_map);
};
#endif // !MANGO_2D_WALL_PATH_H_

