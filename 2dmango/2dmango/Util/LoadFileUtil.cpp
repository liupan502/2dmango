#include "LoadFileUtil.h"
#include <iostream>
#include <fstream>

std::vector<std::string> GetModelIds(std::map<std::string, std::string> parameters) {
  std::vector<std::string> model_ids;
  model_ids.push_back("1");
  model_ids.push_back("2");
  model_ids.push_back("3");
  model_ids.push_back("4");
  return model_ids;
}

QImage GetModelIconImage(std::string modelId) {
  std::string dir_path = "d:\\model\\";
  std::string image_full_path = dir_path + modelId;
  QString q_image_full_path(image_full_path.c_str());
  QImage img(q_image_full_path);
  return img;
}

ModelData* GetModelInfo(const std::string& modelId) {
  
  ModelData* model_data = new ModelData();
  model_data->set_name(modelId);
  std::string info_file_path = "d:\\model\\" + modelId + "\\info";
  std::ifstream file(info_file_path);

  std::string model_name;
  file >> model_name;
  model_data->set_model_name(model_name);
  float width, height, length;
  int model_type;
  file >> width >> height >> length >> model_type;
  model_data->set_width(width);
  model_data->set_height(height);
  model_data->set_length(length);
  model_data->set_model_type(model_type);
  file.close();
  return model_data;
}

QImage GetModelImage(std::string modelId) {
  std::string image_path = "d:\\model\\"+modelId+"\\model.png";
  QString q_image_path(image_path.c_str());
  QImage img(q_image_path);
  return img;
}