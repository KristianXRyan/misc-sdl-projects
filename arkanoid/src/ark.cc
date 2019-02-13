#include "ark.hh"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdexcept>
#include <string>
#include <chrono>

const static std::string TITLE = "Arkanoid";

namespace ark
{
    Arkanoid::Arkanoid()
        : m_window(TITLE, 640u, 480u)
    {
    }
    
    Arkanoid::~Arkanoid()
    {
        SDL_Quit();
    }
    
    void Arkanoid::initGraphics()
    {
        if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
            throw std::runtime_error(std::string("Could not init SDL: ") + 
                SDL_GetError());
        
        if(IMG_Init(0) != 0)
            throw std::runtime_error(std::string("Could not init image: ") + 
                IMG_GetError());
        
        if(TTF_Init() != 0)
            throw std::runtime_error(std::string("Could not init fonts: ") + 
                TTF_GetError());
        
        try
        {
            m_window.show();
        }
        catch(std::exception &e)
        {
            throw;
        }
    }
    
    void Arkanoid::start()
    {
        run();
    }
    
    /* Contains the main game loop  */
    void Arkanoid::run()
    {
        const double FPS = 60.0;
        const double UPS = 25.0;
        
        using namespace std::chrono;
        using sysClock = high_resolution_clock;
        
        const milliseconds oneSecond = milliseconds(1000);
        
        const double timeU = 1000000000 / UPS;
        const double timeF = 1000000000 / FPS;
        
        double deltaUpdate = 0.0;
        double deltaFrames = 0.0;
        
        nanoseconds lastTime = duration_cast<nanoseconds>
            (sysClock::now().time_since_epoch());
            
        nanoseconds currentTime =  duration_cast<nanoseconds>
            (sysClock::now().time_since_epoch());
            
        milliseconds timer = duration_cast<milliseconds>
            (sysClock::now().time_since_epoch());
            
        unsigned int frames = 0;
        unsigned int ticks = 0;
            
        bool running = true;
        
        while(running)
        {
            m_eventHandler.listen();
            running = !m_eventHandler.isPlayerRequestingClose();
            
            currentTime = duration_cast<nanoseconds> 
                (high_resolution_clock::now().time_since_epoch());
            deltaUpdate += (currentTime - lastTime).count() / timeU;
            deltaFrames += (currentTime - lastTime).count() / timeF;
            lastTime = currentTime;
            
            while(deltaUpdate >= 1)
            {
                ticks++;
                deltaUpdate--;
            }
            
            while(deltaFrames >= 1)
            {
                frames++;
                deltaFrames--;
            }
            
            if (duration_cast<milliseconds>(sysClock::now().time_since_epoch())
                - timer >= oneSecond)
            {
                frames = 0;
                ticks = 0;
                timer += oneSecond;
            }
                    
            draw();
        }
    }
    
    void Arkanoid::update()
    {
    
    }
    
    void Arkanoid::draw()
    {
    
    }
}