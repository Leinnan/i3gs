//
// Created by piotr on 09.09.16.
//

#include "Manager.h"

#include <thread>

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
                    this->setDefaultColor(getAllAfterEqualSign(one_line));
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
                        std::istringstream iss(borders_width_string);
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
                        std::istringstream iss(borders_width_string);
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

void Manager::start(const bool& p_is_in_terminal, const bool& p_is_in_xfce) {
    this->is_running = true;
    unsigned int counter = 0;

    if(p_is_in_terminal)
        printf("\033[s"); // save cursor position, hide cursor
    else
        std::cout << "{\"version\":1,\"click_events\":false}\n[[]\n";

    if(this->run_once){
        this->update(p_is_in_terminal,p_is_in_xfce);
        return;
    }

    while(this->is_running){
        if(p_is_in_terminal)
            printf("\033[u\033[K");
        this->update(p_is_in_terminal,p_is_in_xfce);
        while(counter < this->sleep_time){
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            counter++;
        }
        counter = 0;

        if(p_is_in_terminal){
            std::cout << std::flush;
        }
    }
}


void Manager::addBlock(Block p_block)
{
    blocks.push_back(p_block);
}

void Manager::update(const bool& p_is_in_terminal,const bool& p_is_in_xfce )
{

    std::string output = ",\n[";
    if(p_is_in_xfce)
        output = "<txt>";
    else if(p_is_in_terminal)
         output = "";
    for(unsigned int i = 0; i < blocks.size(); i++){
        // for now always update text
        // in future I need to implement better way to handle this
        blocks[i].updateText();



        // if isnt the the first block we need to add comma before adding new block
        if(i != 0 and !p_is_in_xfce){
            output += p_is_in_terminal ? " | " :",";
        }
        if(p_is_in_terminal)
            output += blocks[i].getTerminalOutput();
        else if(p_is_in_xfce)
            output += blocks[i].getPangoOutput();
        else
            output += blocks[i].getFullText();


    }
    //lets close this update
    if(p_is_in_xfce)
        output += "</txt>";
    else if(!p_is_in_terminal)
        output += "]";

    printf(output.c_str());
}

int Manager::getSleepTime() const {
    return sleep_time;
}

void Manager::setSleepTime(int sleep_time) {
    Manager::sleep_time = sleep_time;
}

const std::string &Manager::getDefault_color() const {
    return default_color;
}

void Manager::setDefaultColor(const std::string &p_default_color) {
    Manager::default_color = p_default_color;
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

    std::string battery_script = "if [ $(ls /sys/class/power_supply | grep BAT | wc -l) -gt 0 ]; then\n"
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

Block Manager::getPreset(const std::string &p_name) {
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
