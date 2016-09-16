//
// Created by piotr on 09.09.16.
//

#ifndef I3GS_MANAGER_H
#define I3GS_MANAGER_H
#include <vector>
#include <string>
#include <unistd.h>
#include <iostream>
#include <libconfig.h++>
#include "Block.h"

using namespace std;

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
    int sleep_time;
    bool is_running;
    std::vector < Block > blocks;
    std::string default_color = "#CDCDCD";

};


#endif //I3GS_MANAGER_H
