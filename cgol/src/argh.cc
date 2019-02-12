#include "argh.hh"

#include "config.hh"

#include <vector>
#include <string>
#include <stdexcept>

#include <SDL2/SDL.h>

Arghandler::Arghandler()
    : m_mouse(MANUAL_INIT),m_width(WIDTH),m_height(HEIGHT),m_rows(NUM_ROWS),
    m_cols(NUM_COLUMNS),m_likely(LIKELY),m_ups(UPS),m_fps(FPS),m_fpsSet(false)
{
}

Arghandler::~Arghandler()
{
}

void Arghandler::parseArgs(int argc, char **argv)
{
    if(argc == 1)
        return;
    
    std::vector<std::string> args(argc);
    
    for(int i = 0; i < argc; i++)
    {
        args[i] = argv[i];
    }
    
    for(unsigned int i = 1; i < args.size(); i++)
    { 
        std::string &arg = args[i];
        
        if(arg.compare("-m") == 0)
            m_mouse = true;
        else if(arg.compare("-w") == 0)
        {
            if(i < args.size() - 1)
                m_width = std::stoi(args[++i]);
            else
                throw std::runtime_error(std::string("flag ") + 
                    "-w" + std::string(" does not have an option."));
        }
        else if(arg.compare("-h") == 0)
        {
            if(i < args.size() - 1)
                m_height = std::stoi(args[++i]);
            else
                throw std::runtime_error(std::string("flag ") + 
                    "-h" + std::string(" does not have an option."));
        }
        else if(arg.compare("-r") == 0)
        {
            if(i < args.size() - 1)
                m_rows = std::stoi(args[++i]);
            else
                throw std::runtime_error(std::string("flag ") + 
                    "-r" + std::string(" does not have an option."));
        }
        else if(arg.compare("-c") == 0)
        {
            if(i < args.size() - 1)
                m_cols = std::stoi(args[++i]);
            else
                throw std::runtime_error(std::string("flag ") + 
                    "-c" + std::string(" does not have an option."));
        }
        else if(arg.compare("-u") == 0)
        {
            if(i < args.size() - 1)
                m_ups = std::stod(args[++i]);
            else
                throw std::runtime_error(std::string("flag ") + 
                    "-u" + std::string(" does not have an option."));
        }
        else if(arg.compare("-f") == 0)
        {
            if(i < args.size() - 1)
            {
                m_fps = std::stod(args[++i]);
                m_fpsSet = true;
            }
            else
                throw std::runtime_error(std::string("Error: flag ") + 
                    "-f" + std::string(" does not have an option."));
        }
        else if(arg.compare("-l") == 0)
        {
            if(i < args.size() - 1)
                m_likely = std::stod(args[++i]);
            else
                throw std::runtime_error(std::string("Error: flag ") + 
                    "-l" + std::string(" does not have an option."));
        }
        else
            throw std::runtime_error(std::string("Error: flag not recognized: ")
                + arg);
    }
}

bool Arghandler::isMouseInit() const
{
    return m_mouse;
}

int Arghandler::getWidth() const
{
    return m_width;
}

int Arghandler::getHeight() const
{
    return m_height;
}

int Arghandler::getRows() const
{
    return m_rows;
}

int Arghandler::getCols() const
{
    return m_cols;
}

double Arghandler::getUPS() const
{
    return m_ups;
}

int Arghandler::getLikelyhood() const
{
    return m_likely;
}
    

double Arghandler::getFPS() const
{
    return m_fps;
}

void Arghandler::setRefreshRate(double rr)
{
    /* Sets the frame rate, if SDL could not find the refresh rate of the 
       monitor then it will set it to the default					   */
    if(!m_fpsSet)
        m_fps = rr;
    else if(rr == -1.0) 
        m_fps = FPS;
}