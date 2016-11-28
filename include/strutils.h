#pragma once

#include <string>
#include <vector>

void str_replace(std::string& str, const std::string& from, const std::string& to);
void str_split(const std::string& s, std::vector<std::string>& v, const char c);