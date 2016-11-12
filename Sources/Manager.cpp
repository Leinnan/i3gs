//
// Created by piotr on 09.09.16.
//

#include "Manager.h"

Manager::Manager(const std::string& p_config_path)
{
    this->sleep_time = 1;
    this->is_running = false;

    this->generatePresets();

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
                    this->setDefault_color(getAllAfterEqualSign(one_line));
                }
                if(isStringStartWith(one_line, "sleep_time")){
                    this->setSleepTime(std::stoi(getAllAfterEqualSign(one_line)));
                }
                if(isStringStartWith(one_line, "bg_color")){
                    this->default_background = getAllAfterEqualSign(one_line);
                }
                if(isStringStartWith(one_line, "borders_color")){
                    this->default_borders_color = getAllAfterEqualSign(one_line);
                }
                if(isStringStartWith(one_line, "align")){
                    this->default_align = getAllAfterEqualSign(one_line);
                }
                if(isStringStartWith(one_line, "separator_width")){
                    this->default_separator_block_width = std::stoi(getAllAfterEqualSign(one_line));
                }
                if(isStringStartWith(one_line, "pango")){
                    default_using_markup = one_line.find("true");
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
                if(isStringStartWith(one_line, "preset")){
                    Block preset_block = getPreset(getAllAfterEqualSign(one_line));
                    if(preset_block.getName() != "preset_not_found"){
                        config_block = preset_block;
                    }
                }
                if(isStringStartWith(one_line, "title")){
                    config_block.setTitle(getAllAfterEqualSign(one_line));
                }
                if(isStringStartWith(one_line, "align")){
                    config_block.setAlign(getAllAfterEqualSign(one_line));
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
            config_block = this->getDefaultBlock();
            config_block.setName(getAllBetweenBrackets(one_line));
            is_before_blocks = false;
        }


    }
    if(!is_before_blocks)
        this->addBlock(config_block);
}

void Manager::start() {
    this->is_running = true;
    unsigned counter = 0;
    std::cout << "{\"version\":1,\"click_events\":false}\n[[]" << std::endl;
    while(this->is_running){
        this->update();
        while(counter < this->sleep_time){
            usleep(499999);
            counter++;
        }
        counter = 0;
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

void Manager::generatePresets() {
    Block date = getDefaultBlock();
    date.setName("DATE");
    date.setCommand("date '+%H:%M, %d.%m.%y '");


    Block hdd = getDefaultBlock();
    hdd.setName("HDD");
    hdd.setCommand("df --output=avail -h / |  tail -n 1 | tr -d ' ' | sed 's/G/ GB/g'  | sed 's/M/ MB/g'");

    Block cpu = getDefaultBlock();
    cpu.setName("CPU");
    cpu.setCommand("grep 'cpu ' /proc/stat | awk '{usage=($2+$4)*100/($2+$4+$5)} END {print usage }' | awk '{printf(\"%d%\",$1 + 0.5)}' ");

    Block ram = getDefaultBlock();
    ram.setName("RAM");
    ram.setCommand("free | tail -2 | head -1 | awk '{print $3/$2 * 100.0}' | awk '{printf(\"%d% \",$1 + 0.5)}'");

    Block mpd = getDefaultBlock();
    mpd.setName("MPD");
    mpd.setCommand("mpc | head -1 | sed 's/&/and/g'");

    string battery_script = "if [ $(ls /sys/class/power_supply | grep BAT | wc -l) -gt 0 ]; then\n"
            "    battery_directory=\"/sys/class/power_supply/\"$(ls /sys/class/power_supply | grep BAT | head -1)\"/\"\n"
            "    energy_now=$(<$battery_directory\"/charge_now\")\n"
            "    energy_full=$(<$battery_directory\"/charge_full\")\n"
            "    battery_color=\"\"\n"
            "    charge=$(($energy_now*100))\n"
            "    charge=$(($charge/$energy_full))\n"
            "    \n"
            "#    if [ \"90\" -gt \"$charge\" ]; then\n"
            "#        battery_color=\"color=\\\"da2818\\\"\"\n"
            "#        output=$output\"DSADAS\"\n"
            "#    fi\n"
            "    \n"
            "    status=$(<$battery_directory\"/status\")\n"
            "    charge=$charge\"%\"\n"
            "    echo $charge\n"
            "fi";
    Block bat = getDefaultBlock();
    bat.setName("BAT");
    bat.setCommand(battery_script);

    Block wifi = getDefaultBlock();
    wifi.setName("WIFI");
    wifi.setCommand("iwgetid -r");

    presets.push_back(date);
    presets.push_back(hdd);
    presets.push_back(cpu);
    presets.push_back(ram);
    presets.push_back(mpd);
    presets.push_back(bat);
    presets.push_back(wifi);
}

Block Manager::getPreset(const string &p_name) {
    Block preset_block;
    preset_block.setName("preset_not_found");
    for(unsigned int i = 0; i < presets.size(); i++) {
        if(presets[i].getName() == p_name){
            preset_block = presets[i];
        }
    }
    return preset_block;
}

Block Manager::getDefaultBlock() {
    Block default_block;


    default_block.setBordersWidth(default_borders_width);
    default_block.setColor(default_color);
    default_block.useMarkup(default_using_markup);
    default_block.setBackground(default_background);
    default_block.setBordersColor(default_borders_color);
    default_block.setSeparatorBlockWidth(default_separator_block_width);
    default_block.setAlign(default_align);

    return default_block;
}