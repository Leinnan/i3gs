#ifndef BLOCK_H
#define BLOCK_H
#include <array>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <algorithm>


enum block_align { LEFT, CENTER, RIGHT };


class Block
{
public:
    Block(){};
    ~Block(){};
    std::string execCommand(const char* cmd);
    std::string getFullText();
    void updateText();
    void setAlign(const block_align& align)
    {
        this->align = align;
    }
    void setBordersColor(const std::string& borders_color)
    {
        this->borders_color = borders_color;
    }
    void setColor(const std::string& color)
    {
        this->color = color;
    }
    void setCommand(const std::string& command)
    {
        this->command = command;
    }
    void setSeparatorBlockWidth(int separator_block_width)
    {
        this->separator_block_width = separator_block_width;
    }
    void setTitle(const std::string& title)
    {
        this->title = title;
    }
    void setBordersWidth(const std::array<int, 4> p_borders_width){
        this->borders_width = p_borders_width;
    }
    void useMarkup(bool p_use_markup = true){
        this->using_markup = p_use_markup;
    }
private:
    std::string command = "echo \"none\"";
    std::string title = "";
    std::string content = "";
    std::array<int, 4> borders_width{ { 0, 0, 2, 0 } };
    int separator_block_width = 10;
    std::string borders_color = "none";
    std::string color = "#cdcdcd";
    block_align align;
    bool using_markup = false;
};

#endif // BLOCK_H
