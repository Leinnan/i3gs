#include <iostream>
#include "Sources/Block.h"

using namespace std;

int main(int argc, char **argv)
{
    Block mpd;
    Block bat;
    Block ram;
    Block cpu;
    Block hdd;
    Block date;
    
    mpd.setTitle("<span weight='heavy' fgcolor='#e66601'>   </span>");
    mpd.setBordersColor("#e66601");
    mpd.setCommand("/home/piotr/.skrypty/i3_mpd_status.sh");
    mpd.useMarkup();
    
    bat.setTitle("<span weight='heavy' fgcolor='#407ee7'>   </span>");
    bat.setBordersColor("#407ee7");
    bat.setCommand("/home/piotr/.skrypty/i3_battery.sh");
    bat.useMarkup();
    
    ram.setCommand("free | tail -2 | head -1 | awk '{print $3/$2 * 100.0}' | awk '{printf(\"%d% \",$1 + 0.5)}'");
    ram.setTitle("<span weight='heavy' fgcolor='#cdcdcd'>   </span> ");
    ram.setBordersColor("#198844");
    ram.setBackground("#198844");
    ram.useMarkup();
    
    cpu.setCommand("grep 'cpu ' /proc/stat | awk '{usage=($2+$4)*100/($2+$4+$5)} END {print usage }' | awk '{printf(\"%d%\",$1 + 0.5)}' ");
    cpu.setTitle("<span weight='heavy' fgcolor='#cc342b'>   </span>");
    cpu.setBordersColor("#cc342b");
    cpu.useMarkup();
    
    hdd.setCommand("df --output=avail -h / |  tail -n 1 | tr -d ' ' | sed 's/G/ GB/g'  | sed 's/M/ MB/g'");
    hdd.setTitle("<span weight='heavy' fgcolor='#9e39ed'>   </span>");
    hdd.setBordersColor("#9e39ed");
    hdd.useMarkup();
    
    date.setCommand("date '+%A, %H:%M:%S'");
    
    
    
    cout << "{\"version\":1,\"click_events\":true}" << endl;
    cout << "[[]" << endl;
    while(true){
        mpd.updateText();
        bat.updateText();
        hdd.updateText();
        ram.updateText();
        cpu.updateText();
        date.updateText();
        
        cout << ",[";
        cout << mpd.getFullText();
        cout << "," << bat.getFullText();
        cout << "," << ram.getFullText();
        cout << "," << cpu.getFullText();
        cout << "," << hdd.getFullText();
        cout << "," << date.getFullText();
        cout << "]" << endl; 
    }
    return 0;
}
