# i3-gaps-status
My own status made for i3-gaps.

# build-instructions
Open terminal in repository folder
```build-instructions
mkdir build
cd build 
cmake ..
make
sudo make install
```

For now I dont have any installation progress so this is only way to get it done.

For best effect install Font Awesome from: http://fontawesome.io/

# config file

This is my own config file for example:

```
default_color=#fffaaa


[mpd]
command=/home/piotr/.skrypty/i3_mpd_status.sh
title=<span weight='heavy' fgcolor='#2f343f'>   </span> 
color=#2f343f
bg_color=#7FDBFF
borders_color=#7FDBFF
pango=true
separator_width=0
borders_width=3 3 3 3

[ram]
command=free | tail -2 | head -1 | awk '{print $3/$2 * 100.0}' | awk '{printf("%d% ",$1 + 0.5)}'
title=<span weight='heavy' fgcolor='#2f343f'>   </span> 
color=#2f343f
bg_color=#3D9970
borders_color=#3D9970
pango=true
separator_width=0
borders_width=3 3 3 3

[cpu]
command=grep 'cpu ' /proc/stat | awk '{usage=($2+$4)*100/($2+$4+$5)} END {print usage }' | awk '{printf("%d%",$1 + 0.5)}' 
title=<span weight='heavy' fgcolor='#2f343f'>   </span> 
color=#2f343f
bg_color=#2ECC40
borders_color=#2ECC40
pango=true
separator_width=0
borders_width=3 3 3 3

[battery]
title=<span weight='heavy' fgcolor='#2f343f'>   </span>
color=#2f343f
bg_color=#39CCCC
borders_color=#39CCCC
command=/home/piotr/.skrypty/i3_battery.sh
pango=true
separator_width=0
borders_width=3 3 3 3

[hdd]
command=df --output=avail -h / |  tail -n 1 | tr -d ' ' | sed 's/G/ GB/g'  | sed 's/M/ MB/g'
title=<span weight='heavy' fgcolor='#2f343f'>   </span>
color=#2f343f
borders_color=#01FF70
bg_color=#01FF70
pango=true
separator_width=0
borders_width=3 3 3 3

[date]
command=date '+%A, %H:%M:%S '
title=<span weight='heavy' fgcolor='#2f343f'>   </span> 
color=#2f343f
bg_color=#FFDC00
borders_color=#FFDC00
pango=true
separator_width=0
borders_width=3 3 3 3
```
And this is effect:

![SCREEN](http://i.imgur.com/EvkJjXT.jpg)


If you want to use config file just set status_command like this:
```
status_command i3gs /path/to/the/config
``` 



# ToDo

- [x] config file support
- [ ] make block presets like CPU/RAM usage or current date
- [ ] make presets configurable
