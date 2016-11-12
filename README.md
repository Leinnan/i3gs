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

For best effect install Font Awesome from: http://fontawesome.io/

# config file

This is my own config file for example:

```
borders_width=0 0 2 0
separator_width=10

[mpd]
preset=MPD
title=<span weight='heavy' fgcolor='#7FDBFF'>   </span>
borders_color=#7FDBFF

[ram]
preset=RAM
title=<span weight='heavy' fgcolor='#3D9970'>   </span>
borders_color=#3D9970

[cpu]
preset=CPU
title=<span weight='heavy' fgcolor='#2ECC40'>   </span>
borders_color=#2ECC40

[hdd]
preset=HDD
title=<span weight='heavy' fgcolor='#01FF70'>   </span>
borders_color=#01FF70

[battery]
preset=BAT
title=<span weight='heavy' fgcolor='#39CCCC'>   </span>
borders_color=#39CCCC

[wifi]
preset=WIFI
title=<span weight='heavy' fgcolor='#01FF70'>   </span>
borders_color=#01FF70

[date]
preset=DATE
title=<span weight='heavy' fgcolor='#FFDC00'>   </span>
borders_color=#FFDC00
separator_width=0
```
And this is effect:

![SCREEN](http://i.imgur.com/9ulgqWC.jpg)


If you want to use config file just set status_command like this:
```
status_command i3gs /path/to/the/config
``` 



# ToDo

- [x] config file support
- [x] make block presets like CPU/RAM usage or current date
- [ ] make presets configurable
