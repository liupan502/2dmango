#pragma once
#include <string>
#include <vector>
#include <map>
#include <QImage>
std::vector<std::string> GetModelIds(std::map<std::string, std::string> parameters);

QImage GetModelIconImage(std::string modelId);