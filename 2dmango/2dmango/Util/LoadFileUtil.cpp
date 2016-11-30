#include "LoadFileUtil.h"
#include "const.h"

#include <iostream>
#include <fstream>

std::vector<std::string> GetModelIds(std::map<std::string, std::string> parameters) {
  std::vector<std::string> model_ids;
  const std::string file_name = DEFAULT_MODEL_DIR + "//models";

  std::ifstream models_file(file_name);
  while (!models_file.eof()) {
    std::string model_id;
    models_file >> model_id;
    if (model_id.length() == 0)
      continue;
    model_ids.push_back(model_id);
  }
  models_file.close();  
  return model_ids;
}

QImage GetModelIconImage(std::string modelId) {
  std::string dir_path = "d:\\model\\";
  std::string image_full_path = DEFAULT_MODEL_DIR + "//"+modelId+"//sample.jpg";
  QString q_image_full_path(image_full_path.c_str());
  QImage img(q_image_full_path);
  return img;
}

ModelData* GetModelInfo(const std::string& modelId) {
  
  ModelData* model_data = new ModelData();
  model_data->set_name(modelId);
  std::string info_file_path = DEFAULT_MODEL_DIR +"\\"+ modelId + "\\info";
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
  std::string image_path = DEFAULT_MODEL_DIR +"\\"+modelId+"\\top.png";
  QString q_image_path(image_path.c_str());
  QImage img(q_image_path);
  return img;
}