#include "DesignData.h"
/*
std::vector<WallGeometry> DesignData::ComputeWallGeometrys() {
  std::vector<WallGeometry> wall_geometrys;
  std::map<std::string, WallData*>::iterator it;
  for (it = wall_data_map_.begin(); it != wall_data_map_.end(); it++) {
    WallData* wall_data = it->second;
    if (!wall_data->is_completed()) {      
      std::vector<QPointF> geometry;
      geometry.push_back(wall_data->start_corner_position());
      geometry.push_back(wall_data->end_corner_position());      
      WallGeometry wall_geometry(geometry);
      wall_geometrys.push_back(wall_geometry);
    }
    else {

    }

  }
  return wall_geometrys;
}
*/

std::vector<WallGeometry> DesignData::ComputeWallGeometrys() {
  std::vector<WallGeometry> wall_geometrys;
  std::map<std::string,WallData*>::iterator it;
  for (it = wall_data_map_.begin(); it != wall_data_map_.end(); it++) {
    WallGeometry geometry = it->second->GetGeometry();
    wall_geometrys.push_back(geometry);
  }
  return wall_geometrys;
}

RoomData* DesignData::find_available_room(std::set<RoomData*> excludeRooms, std::set<WallData*> excludeWalls) {
  RoomData* room = NULL;
  std::map<std::string,RoomData* >::iterator it;
  for (it = room_data_map_.begin(); it != room_data_map_.end(); it++) {
    RoomData* tmp_room = it->second;
    if (excludeRooms.find(tmp_room) != excludeRooms.end()) {
      continue;
    }
    if (tmp_room->CanComputeWallGeometry(excludeWalls)) {
      room = tmp_room;
      break;
    }
  }
  return room;
}

void DesignData::UpdateGeometry() {
  reset_geometry();
  update_wall_geometrys();  
}

void DesignData::reset_geometry() {
  std::map<std::string,WallData*>::iterator it;
  for (it = wall_data_map_.begin(); it != wall_data_map_.end(); it++) {
    it->second->ResetGeometry();
  }
}

void DesignData::update_wall_geometrys() {
  std::map<std::string, WallData*>::iterator it;
  for (it = wall_data_map_.begin(); it != wall_data_map_.end(); it++) {
	  if (it->second->status() == DRAWING_WALL_DATA) {
		  it->second->set_status(UNROOM_WALL_DATA);
	  }
  }

  std::set<RoomData*> exclude_rooms;
  std::set<WallData*> exclude_walls;
  while (true) {

    RoomData* room = find_available_room(exclude_rooms, exclude_walls);
   
    if (!room) {
      break;
    }

    if (wall_data_map_.size() == 16) {
      int a = 0;
    }
    exclude_rooms.insert(room);
   
    room->GenerateLines();
    std::vector<WallData*> walls = room->walls();
    for (int i = 0; i < walls.size(); i++) {
      WallData* wall = walls[i];
      if (exclude_walls.find(wall) != exclude_walls.end()) {
        continue;
      }
      exclude_walls.insert(wall);
      update_wall_geometry(wall); 
      CornerData* start_corner = wall->start_corner();
      std::vector<WallData*> start_related_walls = start_corner->RelateWalls();

      bool should_update_corner = true;
      for (int i = 0; i < start_related_walls.size(); i++) {
        if (exclude_walls.find(start_related_walls[i]) == exclude_walls.end()) {
          should_update_corner = false;
          break;
        }
      }
      if (should_update_corner) {        
        start_corner->UpdateCornerPosition();
      }

      should_update_corner = true;
      CornerData* end_corner = wall->end_corner();
      std::vector<WallData*> end_related_walls = end_corner->RelateWalls();
      for (int i = 0; i < end_related_walls.size(); i++) {
        if (exclude_walls.find(end_related_walls[i]) == exclude_walls.end()) {
          should_update_corner = false;
          break;
        }
      }
      if (should_update_corner) {      
        end_corner->UpdateCornerPosition();
      }
    }
  }
  
}

void DesignData::update_corner_positions() {
  std::map<std::string,CornerData*>::iterator it; 

  for (it = corner_data_map_.begin(); it != corner_data_map_.end(); it++) {
    CornerData* corner = it->second;    
    corner->UpdateCornerPosition();
  }
}

void DesignData::update_corner_position(CornerData* corner) {

}

void  DesignData::compute_corner_position(std::string corner_name) {
  CornerData* corner_data = corner_data_map_[corner_name];
  if(corner_data == NULL){
    return;
  }

  if(corner_data->has_position_data()){
    return;
  }
    
  std::vector<WallData*> wall_datas;
  std::map<std::string, WallData*>::iterator it;
  for (it = wall_data_map_.begin(); it != wall_data_map_.end(); it++) {
    WallData* wall_data = it->second;
    if (!wall_data->DoContainCorner(corner_data))
      continue;
    wall_datas.push_back(wall_data);
  }
}

void DesignData::sort_wall(std::vector<WallData*>& wall_datas){
  
}

void DesignData::update_wall_geometry(WallData* wall) {
  
  PointData* point1 = wall->start_corner()->GetPoint(wall->line().start_point_name());
  if (point1 && !point1->has_point_data()) {
    wall->ComputePoint(point1);
  }
     
  PointData* point2 = wall->end_corner()->GetPoint(wall->line().end_point_name());
  if (point2 && !point2->has_point_data()) {
    wall->ComputePoint(point2);
  }
  PointData* point3 = wall->start_corner()->GetPoint(wall->generate_line().start_point_name());
  if (point3 && !point3->has_point_data()) {
    wall->ComputePoint(point3);
  }
  PointData* point4 = wall->end_corner()->GetPoint(wall->generate_line().end_point_name());
  if (point4 && !point4->has_point_data()) {
    wall->ComputePoint(point4);
  }
}