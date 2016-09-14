//
// Created by piotr on 09.09.16.
//

#ifndef I3GS_MANAGER_H
#define I3GS_MANAGER_H
#include <vector>
#include <string>
#include <unistd.h>
#include <iostream>
#include "Block.h"

using namespace std;

class Manager {
public:
    Manager(const std::string& p_config_path);
    void start();
    void addBlock(Block p_block);
    int getSleeep_time() const;
    void setSleeep_time(int sleeep_time);
    const string &getDefault_color() const;
    void setDefault_color(const string &default_color);
private:
    void update();
    int sleeep_time;
    bool is_running;
    std::vector < Block > blocks;
    std::string default_color = "#CDCDCD";

};


#endif //I3GS_MANAGER_H
