#include "WallPath.h"


WallPath::WallPath() :BaseData() {
  ;
}

WallPath::WallPath(std::vector<WallData*> walls) {
  std::string path_name = "";
  for (int i = 0; i < walls.size(); i++) {
    path_name = path_name + walls[i]->name() + "#";
  }
  set_name(path_name);
  walls_ = walls;
}

QJsonObject WallPath::ToJson() {
  return QJsonObject();
}

std::map<std::string, WallPath*> WallPathFactory::CreateWallPaths(std::map<std::string, WallData*> wall_data_map) {
  
  std::vector<WallData*> wall_datas;
  for (std::map<std::string, WallData*>::iterator it = wall_data_map.begin(); it != wall_data_map.end(); it++) {
    wall_datas.push_back(it->second);
  }

  std::map<std::string, WallPath*> wall_paths;
  while (true) {
    if (wall_datas.size() == 0) {
      break;
    }

    std::vector<WallData*> walls;
    WallData* current_wall = NULL;
    CornerData* current_corner = NULL;
    for (int i = 0; i < wall_datas.size(); i++) {
      WallData* tmp_wall = wall_datas[i];
      CornerData* start_corner = tmp_wall->start_corner();
      if (start_corner->RelateWalls().size() > 2) {
        current_wall = tmp_wall;
        current_corner = start_corner;
        break;
      }
      CornerData* end_corner = tmp_wall->end_corner();
      if (end_corner->RelateWalls().size() > 2) {
        current_wall = tmp_wall;
        current_corner = end_corner;
        break;
      }
    }

    if (current_wall == NULL) {
      current_wall = wall_datas[0];
      current_corner = current_wall->start_corner();
    }
    WallData* start_wall = current_wall;
    walls.push_back(current_wall);
    while (true) {
      CornerData* next_corner = NULL;
      if (current_wall->IsStartCorner(current_corner)) {
        next_corner = current_wall->end_corner();
      }
      else {
        next_corner = current_wall->start_corner();
      }

      std::vector<WallData*> relate_walls = next_corner->RelateWalls();
      
      if (next_corner->RelateWalls().size() == 2) {
        if ((relate_walls[0] == start_wall || relate_walls[1] == start_wall) && start_wall != current_wall) {
          break;
        }
        current_wall = relate_walls[0] == current_wall ? relate_walls[1] : relate_walls[0];
        current_corner = next_corner;
        walls.push_back(current_wall);
      }
      else {
        break;
      }

    }

    for (int i = 0; i < walls.size(); i++) {
      std::vector<WallData*>::iterator it = find(wall_datas.begin(), wall_datas.end(), walls[i]);
      if (it != wall_datas.end()) {
        wall_datas.erase(it);
      }
    }
    WallPath* wall_path = new WallPath(walls);
    wall_paths.insert(make_pair(wall_path->name(),wall_path));
  }

  return wall_paths;
}

bool WallPath::DoContianWall(WallData* wall) {
  bool result = false;
  for (int i = 0; i < walls_.size(); i++) {
    if (walls_[i] == wall) {
      result = true;
      break;
    }
  }
  return result;
}

CornerData* WallPath::start_corner() {
  CornerData* corner = NULL;
  if (walls_.size() == 1) {
    corner = walls_[0]->start_corner();
  }

  if (walls_.size() > 1) {
    corner = walls_[0]->start_corner()->RelateWalls().size() == 2 ? walls_[0]->end_corner() :
      walls_[0]->start_corner();
  }
  return corner;
}

CornerData* WallPath::end_corner() {
  CornerData* corner = NULL;
  if (walls_.size() == 1) {
    corner = walls_[0]->end_corner();
  }
  
  if (walls_.size() > 1) {
    int size = walls_.size();
    corner = walls_[size - 1]->start_corner()->RelateWalls().size() == 2 ? walls_[size - 1]->end_corner() :
      walls_[size - 1]->start_corner();
  }

  return corner;
}

bool WallPath::IsStartCorner(CornerData* corner) {
  return (corner == start_corner());
}

bool WallPath::IsEndCorner(CornerData* corner) {
  return (corner == end_corner());
}

bool WallPath::DoContianCorner(CornerData* corner) {
  return (IsStartCorner(corner) || (IsEndCorner(corner)));
}

std::vector<WallData*> WallPath::walls() {
  return walls_;
}

bool WallPath::IsUnshare(std::set<WallPath*> excludeWallPaths) {
  int size = walls_.size();
  if (size == 0) {
    return false;
  }
  
  std::set<WallData*> exclude_wall_datas;
  for (std::set<WallPath*>::iterator path_it = excludeWallPaths.begin(); path_it != excludeWallPaths.end(); path_it++) {
    WallPath* tmp_path = *path_it;
    std::vector<WallData*> sub_wall_datas = tmp_path->walls();
    exclude_wall_datas.insert(sub_wall_datas.begin(), sub_wall_datas.end());
  }

  int size1 = start_corner()->RelateWallSize(exclude_wall_datas);
  int size2 = end_corner()->RelateWallSize(exclude_wall_datas);
  if (size1 == 2 || size2 == 2) {
    return true;
  }
  return false;  
}

WallPath WallPath::GetRoom(std::set<WallPath*> excludeWallPaths) {
  int size = walls_.size();
  if (size == 0) {
    return WallPath();
  }

  std::set<WallData*> exclude_wall_datas;
  for (std::set<WallPath*>::iterator path_it = excludeWallPaths.begin(); path_it != excludeWallPaths.end(); path_it++) {
    WallPath* tmp_path = *path_it;
    std::vector<WallData*> sub_wall_datas = tmp_path->walls();
    exclude_wall_datas.insert(sub_wall_datas.begin(), sub_wall_datas.end());
  }

  WallData* wall = walls_[0];
  std::vector<WallData*> walls = wall->GetRoom(exclude_wall_datas);
  return WallPath(walls);
}

