#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include "Sources/Block.h"
#include "Sources/Manager.h"


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

	if(isatty(STDOUT_FILENO)){
		std::clog << "Detected output to console.\nThanks for using i3gs!\n";
		status.start(true);
	}
	else
		status.start(false);
    
    return 0;
}
