//
// Created by piotr on 09.09.16.
//

#include "Manager.h"

Manager::Manager(const std::string& p_config_path)
{
    this->sleep_time = 10000;
    this->is_running = false;

    if(p_config_path == "none")
        return;
    else
        this->readConfigFile(p_config_path);

}

void Manager::readConfigFile(const std::string& p_config_path)
{
    std::ifstream config_file(p_config_path.c_str());
    std::string one_line;
    Block config_block;

    bool is_before_blocks = true;
    if(!config_file.good()){
        return;
    }
    while(std::getline(config_file, one_line)){
        if(!isStringStartWith(one_line, "[")){
            if(is_before_blocks){
                if(isStringStartWith(one_line, "color")){
                    this->default_color = getAllAfterEqualSign(one_line);
                }
                if(isStringStartWith(one_line, "pango")){
                    if(one_line.find("true"))
                        default_using_markup = true;
                    else
                        default_using_markup = false;
                }
                if(isStringStartWith(one_line, "borders_width")){
                    std::array<int, 4> borders_width{ { 0, 0, 2, 0 } };
                    std::string borders_width_string = getAllAfterEqualSign(one_line);
                    unsigned int spaces_in_result = 0;

                    for(unsigned int i = 0; i < borders_width_string.size() - 1; i++){
                        if(borders_width_string[i] == ' ' && borders_width_string[i+1] != ' ' ){
                            spaces_in_result++;
                        }
                    }
                    if(spaces_in_result >= 3){
                        istringstream iss(borders_width_string);
                        int one_border_width = 0;
                        unsigned int i = 0;
                        while(iss >> one_border_width && i <= 3){
                            borders_width[i] = one_border_width;
                            i++;
                        }
                        default_borders_width = borders_width;
                    }

                }
            }
            else{
                if(isStringStartWith(one_line, "title")){
                    config_block.setTitle(getAllAfterEqualSign(one_line));
                }
                if(isStringStartWith(one_line, "color")){
                    config_block.setColor(getAllAfterEqualSign(one_line));
                }
                if(isStringStartWith(one_line, "bg_color")){
                    config_block.setBackground(getAllAfterEqualSign(one_line));
                }
                if(isStringStartWith(one_line, "borders_color")){
                    config_block.setBordersColor(getAllAfterEqualSign(one_line));
                }
                if(isStringStartWith(one_line, "command")){
                    config_block.setCommand(getAllAfterEqualSign(one_line));
                }
                if(isStringStartWith(one_line, "separator_width")){
                    config_block.setSeparatorBlockWidth(std::stoi(getAllAfterEqualSign(one_line)));
                }
                if(isStringStartWith(one_line, "borders_width")){
                    std::array<int, 4> borders_width{ { 0, 0, 2, 0 } };
                    std::string borders_width_string = getAllAfterEqualSign(one_line);
                    unsigned int spaces_in_result = 0;

                    for(unsigned int i = 0; i < borders_width_string.size() - 1; i++){
                        if(borders_width_string[i] == ' ' && borders_width_string[i+1] != ' ' ){
                            spaces_in_result++;
                        }
                    }
                    if(spaces_in_result >= 3){
                        istringstream iss(borders_width_string);
                        int one_border_width = 0;
                        unsigned int i = 0;
                        while(iss >> one_border_width && i <= 3){
                            borders_width[i] = one_border_width;
                            i++;
                        }
                        config_block.setBordersWidth(borders_width);
                    }

                }
                if(isStringStartWith(one_line, "pango")){
                    if(one_line.find("true"))
                        config_block.useMarkup(true);
                    else
                        config_block.useMarkup(false);
                }
            }
        }
        else{
            if(!is_before_blocks){
                this->addBlock(config_block);
            }
            config_block.resetValues();
            config_block.useMarkup(this->default_using_markup);
			config_block.setBordersWidth(this->default_borders_width);
            config_block.setName(getAllBetweenBrackets(one_line));
            is_before_blocks = false;
        }


    }
    if(!is_before_blocks)
        this->addBlock(config_block);
}

void Manager::start() {
    this->is_running = true;
    std::cout << "{\"version\":1,\"click_events\":false}\n[[]" << std::endl;
    while(this->is_running){
        this->update();
        usleep(this->sleep_time);
    }
}

void Manager::addBlock(Block p_block)
{
    blocks.push_back(p_block);
}

void Manager::update()
{
    std::string output = ",\n[";
    for(unsigned int i = 0; i < blocks.size(); i++){
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

int Manager::getSleepTime() const {
    return sleep_time;
}

void Manager::setSleepTime(int sleep_time) {
    Manager::sleep_time = sleep_time;
}

const string &Manager::getDefault_color() const {
    return default_color;
}

void Manager::setDefault_color(const string &default_color) {
    Manager::default_color = default_color;
}
