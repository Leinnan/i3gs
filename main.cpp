#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string> 
#include "Sources/Block.h"
#include "Sources/Manager.h"

std::string getParentProcessName(){
    std::string parent_process_path = "/proc/";
    parent_process_path += std::to_string(getppid());
    parent_process_path += "/cmdline";

    std::string parent_process_name;
    std::ifstream infile(parent_process_path);
    std::getline(infile, parent_process_name);
    infile.close();
    
    return parent_process_name;
}


int main(int argc, char* argv[])
{
    std::string config_path = "none";
    if(argc > 1){
        config_path = argv[1];
    }
    
    Block mp3;
    Block mpd;
    Block bat;
    Block ram;
    Block cpu;
    Block hdd;
    Block date;
    Manager status(config_path);

    if(config_path == "none"){
        status.setDefaultBordersColor("#e66601");
        status.setDefaultBackgroundColor("#2a2aFF");
        status.addBlock(status.getPreset("HDD"));
        status.addBlock(status.getPreset("CPU"));
        status.addBlock(status.getPreset("RAM"));
        status.addBlock(status.getPreset("DATE"));
    }
    
    
    if(getParentProcessName().find("xfce4/panel") != std::string::npos){
		status.setRunOnce();
		status.start(false,true);
	}

	if(isatty(STDOUT_FILENO)){
		std::clog << "Detected output to console.\nThanks for using i3gs!\n";
		status.start(true,false);
	}
	else
		status.start();
    
    return 0;
}
