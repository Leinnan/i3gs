//
// Created by piotr on 09.09.16.
//

#include "Manager.h"

Manager::Manager(const std::string& p_config_path)
{
    this->sleeep_time = 10000;
    this->is_running = false;
}


void Manager::start() {
    this->is_running = true;
    std::cout << "{\"version\":1,\"click_events\":true}\n[[]" << std::endl;
    while(this->is_running){
        this->update();
        usleep(this->sleeep_time);
    }
}

void Manager::addBlock(Block p_block)
{
    blocks.push_back(p_block);
}

void Manager::update()
{
    std::string output = ",\n[";
    for(int i = 0; i < blocks.size(); i++){
        // for now always update text
        // in future I need to implement better way to handle this
        blocks[i].updateText();



        // if isnt the the first block we need to add comma before adding new block
        if(i != 0){
            output += ",";
        }
        output += blocks[i].getFullText();


    }
    //lets close this update
    output += "]";

    std::cout << output;
}

int Manager::getSleeep_time() const {
    return sleeep_time;
}

void Manager::setSleeep_time(int sleeep_time) {
    Manager::sleeep_time = sleeep_time;
}

const string &Manager::getDefault_color() const {
    return default_color;
}

void Manager::setDefault_color(const string &default_color) {
    Manager::default_color = default_color;
}
