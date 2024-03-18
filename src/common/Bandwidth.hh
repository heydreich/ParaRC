#ifndef _BANDWIDTH_HH_
#define _BANDWIDTH_HH_

#include "../inc/include.hh"
#include "../util/tinyxml2.h"

using namespace tinyxml2;

class Bandwidth {
  public:
    Bandwidth(std::string& filePath);
    ~Bandwidth();
 
    //nodeid -> (upload, download)
    std::unordered_map<int, std::pair<double, double>> _ip2bdwt;

};
#endif
