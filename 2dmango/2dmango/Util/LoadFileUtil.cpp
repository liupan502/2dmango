#include "LoadFileUtil.h"

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