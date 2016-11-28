#include "strutils.h"

void str_replace(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

void str_split(const std::string& s, std::vector<std::string>& v, const char c)
{
	std::string::size_type pos1, pos2;
  	pos2 = s.find(c);
	pos1 = 0;
	while(std::string::npos != pos2) {
    	v.push_back(s.substr(pos1, pos2-pos1));
    	pos1 = pos2 + 1;
    	pos2 = s.find(c, pos1);
	}
	if(pos1 != s.length())
		v.push_back(s.substr(pos1));
	if(s[s.size() - 1] == c)
		v.push_back("");
	if(v.size() == 0)
		v.push_back(s);
}