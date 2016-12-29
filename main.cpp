#include <unistd.h>
#include <iostream>
#include "Sources/Block.h"
#include "Sources/Manager.h"

using namespace std;

int main(int argc, char* argv[])
{
    bool is_term_output = false;
    if(isatty(STDOUT_FILENO) == 1)
		is_term_output = true;
		
	std::clog << "Test: " << isatty(STDOUT_FILENO) << "\t" << STDOUT_FILENO << '\n';
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

	status.start(is_term_output);
    return 0;
}
