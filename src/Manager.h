//
// Created by piotr on 09.09.16.
//

#ifndef I3GS_MANAGER_H
#define I3GS_MANAGER_H
#include <vector>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include "Block.h"


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
    void start(const bool& p_is_in_terminal = false, const bool& p_is_in_xfce = false);
    void addBlock(Block p_block);
    int getSleepTime() const;
    void setSleepTime(int sleep_time);
    const std::string &getDefault_color() const;
    void setDefaultColor(const std::string &p_default_color);
    inline void setDefaultBordersColor(const std::string &p_new_color){ default_borders_color = p_new_color;};
    inline void setDefaultBackgroundColor(const std::string &p_new_color){ default_background = p_new_color;};
    Block getPreset(const std::string &p_name);
    Block getDefaultBlock();
    inline void setRunOnce(const bool &p_run_once = true){this->run_once = p_run_once;};
private:
    void generatePresets();
    void update(const bool& p_is_in_terminal = false, const bool& p_is_in_xfce = false);
    void readConfigFile(const std::string& p_config_path);
    unsigned int sleep_time;
    bool is_running;
    std::vector < Block > blocks;
    std::vector < Block > presets;
    std::string default_color = "#CDCDCD";
    std::string default_title = "";
    std::string default_name = "";
    std::string default_content = "";
    std::string default_align = "center";
    std::string default_background = "none";
    std::string default_borders_color = "none";
    std::array<int, 4> default_borders_width{ { 0, 0, 2, 0 } };
    int default_separator_block_width = 10;
    bool default_using_markup = true;
    bool run_once = false;

};


#endif //I3GS_MANAGER_H
