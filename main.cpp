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
    mpd.setColor("#2f343f");
    mpd.setBackground("#E3DBC8");
    mpd.setBordersColor("#E3DBC8");
    mpd.setBordersWidth(2,2,2,2);
    mpd.setCommand("/home/piotr/.skrypty/i3_mpd_status.sh");
    mpd.useMarkup();
    mpd.setSeparatorBlockWidth(0);
    
    bat.setTitle("<span weight='heavy' fgcolor='#407ee7'>   </span>");
    bat.setBordersColor("#407ee7");
    bat.setCommand("/home/piotr/.skrypty/i3_battery.sh");
    bat.useMarkup();
    bat.setSeparatorBlockWidth(0);
    
    ram.setCommand("free | tail -2 | head -1 | awk '{print $3/$2 * 100.0}' | awk '{printf(\"%d% \",$1 + 0.5)}'");
    ram.setTitle("<span weight='heavy' fgcolor='#2f343f'>   </span> ");
    ram.setBordersColor("#93B470");
    ram.setColor("#2f343f");
    ram.setBackground("#93B470");
    ram.setBordersWidth(2,0,2,0);
    ram.useMarkup();
    ram.setSeparatorBlockWidth(0);
    
    cpu.setCommand("grep 'cpu ' /proc/stat | awk '{usage=($2+$4)*100/($2+$4+$5)} END {print usage }' | awk '{printf(\"%d%\",$1 + 0.5)}' ");
    cpu.setTitle("<span weight='heavy' fgcolor='#2f343f'>   </span>");
    cpu.setColor("#2f343f");
    cpu.setBackground("#cc342b");
    cpu.setBordersColor("#cc342b");
    cpu.setBordersWidth(2,2,2,2);
    cpu.useMarkup();
    cpu.setSeparatorBlockWidth(0);
    
    hdd.setCommand("df --output=avail -h / |  tail -n 1 | tr -d ' ' | sed 's/G/ GB/g'  | sed 's/M/ MB/g'");
    hdd.setTitle("<span weight='heavy' fgcolor='#2f343f'>   </span>");
    hdd.setColor("#2f343f");
    hdd.setBackground("#5A93DB");
    hdd.setBordersColor("#5A93DB");
    hdd.setBordersWidth(2,2,2,2);
    hdd.useMarkup();
    hdd.setSeparatorBlockWidth(0);
    
    date.setCommand("date '+%A, %H:%M:%S'");
    date.setColor("#2f343f");
    date.setBackground("#DACAB6");
    
    
    
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
