#include "Block.h"

std::string Block::execCommand(const char* cmd) {
    char buffer[128];
    std::string result = "";
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer, 128, pipe.get()) != NULL)
            result += buffer;
    }
    result.erase(std::remove(result.begin(), result.end(), '\n'), result.end()); // remove new line char
    return result;
}

void Block::updateText(){
    this->content = execCommand(this->command.c_str());
}


std::string Block::getFullText(){
    std::string m_result  = "{\"\":\"\",\"full_text\":\"";
    m_result += this->title + " " + this->content;
    m_result += "\",\"name\":\"" + this->title;
    m_result += "\",\"separator_block_width\":" + std::to_string(this->separator_block_width);
    if(this->using_markup)
        m_result += ",\"markup\":\"pango\"";
    else
        m_result += ",\"markup\":\"none\"";
    if(this->borders_color != "none")
        m_result += ", \"border\": \"" + this->borders_color + "\"";
    m_result += ", \"border_bottom\": " + std::to_string(borders_width[2]);
    m_result += ",\"border_right\": " + std::to_string(borders_width[1]);
    m_result += ",\"border_left\": " + std::to_string(borders_width[3]);
    m_result += ",\"border_top\":" + std::to_string(borders_width[0]);
    m_result += " }";
    if(this->content == ""){
        m_result = "{\"full_text\":\"\"}";
    }
    return m_result;
}