#include "EditorTD/config.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::string DEFAULT_FONT = "Null";
std::string DEFAULT_FONT_PATH = "Null_path";
int FRAME_BLEED_DIST = 0;
float  WIDGETS_GAP = 0.f;
float  OUTLINE_WIDTH = 0.f;
float  BEVEL_DIST = 0.f;

bool ETD_configure() 
{
    std::cout << "[Edtor TD - Configure] __init__ locating config.env" << std::endl;
	std::ifstream config_file("config.env");
    std::string line;
    if (config_file.is_open())
    {
        std::cout << "[Edtor TD - Configure] config.env - FOUND \n - Configuring" << std::endl;
        while (std::getline(config_file, line))
        {
            std::istringstream is_line(line);
            std::string key;
            std::string value;
            is_line >> key >> value;
            if (key == "#") continue;
            else if (key == "DEFAULT_FONT")
            {
                DEFAULT_FONT = value;
                continue;
            }
            else if (key == "DEFAULT_FONT_PATH")
            {
                DEFAULT_FONT_PATH = value;
                continue;
            }
            else if (key == "FRAME_BLEED_DIST")
            {
                FRAME_BLEED_DIST = std::stoi(value);
                continue;
            }
            else if (key == "WIDGETS_GAP")
            {
                WIDGETS_GAP = std::stof(value);
                continue;
            }
            else if (key == "OUTLINE_WIDTH")
            {
                OUTLINE_WIDTH = std::stof(value);
                continue;
            }
            else if (key == "BEVEL_DIST")
            {
                BEVEL_DIST = std::stof(value);
                continue;
            }
        }
        config_file.close();
        std::cout << "[Edtor TD - Configure DONE] \n Start Program \n" << std::endl;
        return true;
    }
    else
    {
        std::cout << "[Edtor TD - Configure FAILED] config.env - NOT FOUND" << std::endl;
        throw std::runtime_error("[Edtor TD - Configure FAILED] to find configuration file");
        return false;
    }
}