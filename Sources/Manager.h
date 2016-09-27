//
// Created by piotr on 09.09.16.
//

#ifndef I3GS_MANAGER_H
#define I3GS_MANAGER_H
#include <vector>
#include <string>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include "Block.h"

using namespace std;

inline bool isStringStartWith(const std::string& p_base_string, const std::string& p_search_term){
    if(p_base_string.find(p_search_term) == 0)
        return true;
    else
        return false;
}
inline std::string getAllAfterEqualSign(const std::string& p_base_string){
    return p_base_string.substr(p_base_string.find("=")+1);
}
inline std::string getAllBetweenBrackets(const std::string& p_base_string){
    return  p_base_string.substr(p_base_string.find("[")+1,p_base_string.find("]")-p_base_string.find("[")-1);
}

class Manager {
public:
    Manager(const std::string& p_config_path = "none");
    void start();
    void addBlock(Block p_block);
    int getSleep_time() const;
    void setSleep_time(int sleep_time);
    const string &getDefault_color() const;
    void setDefault_color(const string &default_color);
private:
    void update();
    void readConfigFile(const std::string& p_config_path);
    int sleep_time;
    bool is_running;
    std::vector < Block > blocks;
    std::string default_color = "#CDCDCD";

};


#endif //I3GS_MANAGER_H
