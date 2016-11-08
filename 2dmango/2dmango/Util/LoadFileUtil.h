#pragma once
#include <string>
#include <vector>
#include <map>
#include <QImage>
#include "Entity/ModelData.h"
std::vector<std::string> GetModelIds(std::map<std::string, std::string> parameters);

QImage GetModelIconImage(std::string modelId);

ModelData* GetModelInfo(const std::string& modelId = "desk");