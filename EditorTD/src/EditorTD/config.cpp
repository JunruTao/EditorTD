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

unsigned int INIT_WIN_WIDTH = 800;
unsigned int INIT_WIN_HEIGHT = 600;
unsigned int INIT_WIN_WIDTH_MIN = 400;
unsigned int INIT_WIN_HEIGHT_MIN = 400;

sf::Color Col_SREEN_BACKGROUND = { 40,  40,  40,  255 };
sf::Color Col_WIDGET_BACKGROUND = { 70,  70,  70,  255 };
sf::Color Col_WIDGET_BORDER = { 150, 150, 150, 255 };
sf::Color Col_EDIT_TEXT = { 255, 255, 0, 255 };
sf::Color Col_STATIC_TEXT = { 187, 187, 187, 255 };



bool ETD::Config::Load_ConfigurationFiles() 
{
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
        return true;
    }
    else
    {
        std::cout << "[Edtor TD - Configure FAILED] config.env - NOT FOUND" << std::endl;
        throw std::runtime_error("[Edtor TD - Configure FAILED] to find configuration file");
        return false;
    }
}





bool ETD::Config::Configure()
{
    std::cout << "[Edtor TD - Configure] __init__ locating config.env" << std::endl;
    if (ETD::Config::Load_ConfigurationFiles()) 
    {
        std::cout << "[Edtor TD - Configure DONE] \n Start Program \n" << std::endl;
        return true;
    }
    else 
    {
        std::cout << "[Edtor TD - Configure FAILED]" << std::endl;
        return false;
    }
}

bool ETD::Config::Reload_Config()
{
    std::cout << "[Edtor TD - Reload_Configure] locating config.env" << std::endl;
    if (ETD::Config::Load_ConfigurationFiles())
    {
        std::cout << "[Edtor TD - Reconfigure DONE] \n" << std::endl;
        return true;
    }
    else
    {
        std::cout << "[Edtor TD - Reconfigure FAILED]" << std::endl;
        return false;
    }
}
