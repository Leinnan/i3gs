#include <unistd.h>
#include <iostream>
#include "Sources/Block.h"
#include "Sources/Manager.h"

using namespace std;

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


        mp3.setTitle("<span weight='heavy' fgcolor='#2f343f'>   </span>");
        mp3.setColor("#2f343f");
        mp3.setBackground("#0074D9");
        mp3.setBordersColor("#0074D9");
        mp3.setBordersWidth(2,2,2,2);
        mp3.setCommand("/home/piotr/.scripts/deadbeef_status.sh");
        mp3.useMarkup();
        mp3.setSeparatorBlockWidth(0);

        mpd.setTitle("<span weight='heavy' fgcolor='#2f343f'>   </span>");
        mpd.setColor("#2f343f");
        mpd.setBackground("#7FDBFF");
        mpd.setBordersColor("#7FDBFF");
        mpd.setBordersWidth(2,2,2,2);
        mpd.setCommand("/home/piotr/.skrypty/i3_mpd_status.sh");
        mpd.useMarkup();
        mpd.setSeparatorBlockWidth(0);

        bat.setTitle("<span weight='heavy' fgcolor='#2f343f'>   </span>");
        bat.setBordersColor("#39CCCC");
        bat.setBackground("#39CCCC");;
        bat.setColor("#2f343f");
        bat.setBordersWidth(2,2,2,2);
        bat.setCommand("/home/piotr/.skrypty/i3_battery.sh");
        bat.useMarkup();
        bat.setSeparatorBlockWidth(0);

        ram.setCommand("free | tail -2 | head -1 | awk '{print $3/$2 * 100.0}' | awk '{printf(\"%d% \",$1 + 0.5)}'");
        ram.setTitle("<span weight='heavy' fgcolor='#2f343f'>   </span> ");
        ram.setBordersColor("#3D9970");
        ram.setColor("#2f343f");
        ram.setBackground("#3D9970");
        ram.setBordersWidth(2,2,2,2);
        ram.useMarkup();
        ram.setSeparatorBlockWidth(0);

        cpu.setCommand("grep 'cpu ' /proc/stat | awk '{usage=($2+$4)*100/($2+$4+$5)} END {print usage }' | awk '{printf(\"%d%\",$1 + 0.5)}' ");
        cpu.setTitle("<span weight='heavy' fgcolor='#2f343f'>   </span>");
        cpu.setColor("#2f343f");
        cpu.setBackground("#2ECC40");
        cpu.setBordersColor("#2ECC40");
        cpu.setBordersWidth(2,4,2,4);
        cpu.useMarkup();
        cpu.setSeparatorBlockWidth(0);

        hdd.setCommand("df --output=avail -h / |  tail -n 1 | tr -d ' ' | sed 's/G/ GB/g'  | sed 's/M/ MB/g'");
        hdd.setTitle("<span weight='heavy' fgcolor='#2f343f'>   </span>");
        hdd.setColor("#2f343f");
        hdd.setBackground("#01FF70");
        hdd.setBordersColor("#01FF70");
        hdd.setBordersWidth(2,2,2,2);
        hdd.useMarkup();
        hdd.setSeparatorBlockWidth(0);

        date.setCommand("date '+%A, %H:%M:%S '");
        date.setColor("#2f343f");
        date.setBackground("#FFDC00");
        date.setBordersColor("#FFDC00");
        date.setBordersWidth(2,2,2,2);
        date.setTitle("<span weight='heavy' fgcolor='#2f343f'>   </span>");
        date.useMarkup();

        status.addBlock(mp3);
        status.addBlock(mpd);
        status.addBlock(bat);
        status.addBlock(hdd);
        status.addBlock(ram);
        status.addBlock(cpu);
        status.addBlock(date);

    }

    status.start();
    return 0;
}
