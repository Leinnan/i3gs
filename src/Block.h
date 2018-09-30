#ifndef BLOCK_H
#define BLOCK_H
#include <array>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <algorithm>




class Block
{
public:
    Block();
    ~Block(){};
    std::string execCommand(const char* cmd);
    std::string getFullText();
	std::string getTerminalOutput();
	std::string getPangoOutput();
    void updateText();
    void setAlign(const std::string& align)
    {
        this->align = align;
    }
    void setBordersColor(const std::string& borders_color)
    {
        this->borders_color = borders_color;
    }
    void setColor(const std::string& p_color)
    {
        this->color = p_color;
    }
    void setCommand(const std::string& command)
    {
        this->command = command;
    }
    void setName(const std::string& name)
    {
        this->name = name;
    }
    void setSeparatorBlockWidth(int separator_block_width)
    {
        this->separator_block_width = separator_block_width;
    }
    void setTitle(const std::string& p_title)
    {
        this->title = p_title;
    }
    void setBackground(const std::string& p_background)
    {
        this->background = p_background;
    }
    void setBordersWidth(const std::array<int, 4> p_borders_width)
    {
        this->borders_width = p_borders_width;
    }
    void setBordersWidth(const int& p_border_width_1, const int& p_border_width_2, const int& p_border_width_3, const int& p_border_width_4)
    {
        this->borders_width[0] = p_border_width_1;
        this->borders_width[1] = p_border_width_2;
        this->borders_width[2] = p_border_width_3;
        this->borders_width[3] = p_border_width_4;
    }
    void useMarkup(bool p_use_markup = true){
        this->using_markup = p_use_markup;
    }
    const std::string &getName() const;
    void setPangoFont(const std::string& p_pango_font){
        this->pango_font = p_pango_font;
    }
    const std::array<int, 4> &getBorders_width() const;
    void resetValues();
private:
    std::string command = "echo \"none\"";
    std::string title = "";
    std::string name = "";
    std::string content = "";
    std::string background = "none";
    std::string borders_color = "none";
    std::string color = "#cdcdcd";
    std::string pango_font = "";
    std::array<int, 4> borders_width;
    int separator_block_width = 10;
    std::string align = "center";
    bool using_markup = true;
};

#endif // BLOCK_H
