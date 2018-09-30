#include "Block.h"

std::string Block::execCommand(const char* cmd) {
    char buffer[128];
    std::string command = cmd;
    command += " 2> /dev/null";//dont display error
    std::string result = "";
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer, 128, pipe.get()) != NULL)
            result += buffer;
    }
    result.erase(std::remove(result.begin(), result.end(), '\n'), result.end()); // remove new line char
    return result;
}

Block::Block() :
borders_width{ { 0, 0, 2, 0 } }{
}

void Block::updateText(){
    this->content = execCommand(this->command.c_str());
}

std::string Block::getTerminalOutput(){
	return this->title + " " + this->content;
}

std::string Block::getPangoOutput(){
	std::string m_result = "<span ";
	
    if(this->background != "none") {
        m_result += "background='" + this->background + "'";
    }

	m_result += " >";
	m_result +=this->title + " " + this->content;
	m_result += "</span>";
	return m_result;
}

std::string Block::getFullText(){
	// if no content make it faster
    if(this->content == ""){
        return "{\"full_text\":\"\"}";
    }
	
    std::string m_result  = "{\"\":\"\",\"full_text\":\"";
    m_result += this->title + " " + this->content;
    m_result += "\",\"name\":\"" + this->name;
    m_result += "\",\"separator_block_width\":" + std::to_string(this->separator_block_width);
    if(this->using_markup)
        m_result += ",\"markup\":\"pango\"";
    else
        m_result += ",\"markup\":\"none\"";
    if(this->background != "none")
        m_result += ", \"background\": \"" + this->background + "\"";
    if(this->borders_color != "none")
        m_result += ", \"border\": \"" + this->borders_color + "\"";
    m_result += ", \"border_bottom\": " + std::to_string(borders_width[2]);
    m_result += ",\"border_right\": " + std::to_string(borders_width[1]);
    m_result += ",\"border_left\": " + std::to_string(borders_width[3]);
    m_result += ",\"border_top\":" + std::to_string(borders_width[0]);
    m_result += ", \"color\": \"" + this->color + "\"";
    m_result += ", \"align\": \"" + this->align + "\"";
    m_result += " }";
    
    return m_result;
}

void Block::resetValues() {

    this->command = "echo \"none\"";
    this->title = "";
    this->content = "";
    this->background = "none";
    this->borders_width = { { 0, 0, 2, 0 } };
    this->separator_block_width = 10;
    this->borders_color = "none";
    this->color = "#cdcdcd";
    this->using_markup = false;
}

const std::string &Block::getName() const {
    return name;
}

const std::array<int, 4> &Block::getBorders_width() const {
    return borders_width;
}
