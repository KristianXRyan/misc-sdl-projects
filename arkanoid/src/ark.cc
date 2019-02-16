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
        const double fps = 60.0;
        const double tps = 25.0;
    
        using namespace std::chrono;
        using sysClock = high_resolution_clock;
        
        /* For determining when a second has passed  */
        const milliseconds oneSecond = milliseconds(1000);
        /* For determining how many frames to render and how many updates
           to run in a second             */
        const double timeUpdate = 1000000000 / fps;
        const double timeFrames = 1000000000 / tps;
        
        /* variable length delta time data */
        double deltaUpdate = 0.0;
        double deltaFrames = 0.0;
        
        /* For determining how much time has passed since the last
           run of the loop             */
        nanoseconds lastTime = duration_cast<nanoseconds>
            (sysClock::now().time_since_epoch());
            
        nanoseconds currentTime =  duration_cast<nanoseconds>
            (sysClock::now().time_since_epoch());
            
        milliseconds timer = duration_cast<milliseconds>
            (sysClock::now().time_since_epoch());
        
        /* For keeping track of the frame and update rate  */    
        unsigned int frames = 0;
        unsigned int ticks = 0;
            
        bool isRunning = true;
        
        while(isRunning)
        {
            // event stuff
            m_eventHandler.listen();
            isRunning = !m_eventHandler.isPlayerRequestingClose();

            currentTime = duration_cast<nanoseconds>
                (sysClock::now().time_since_epoch());
            deltaUpdate += (currentTime - lastTime).count() / timeUpdate;
            deltaFrames += (currentTime - lastTime).count() / timeFrames;
            lastTime = currentTime;
            
            while(deltaUpdate >= 1)
            {
                tick();
                ticks++;
                deltaUpdate--;
            }
            
            while(deltaFrames >= 1)
            {
                draw();
                frames++;
                deltaFrames--;
            }
            
            if (duration_cast<milliseconds>(sysClock::now().time_since_epoch())
                - timer >= oneSecond)
            {
                frames = 0;
                ticks  = 0;
                timer  += oneSecond;
            }
        }
    }
    
    void Arkanoid::tick()
    {
    
    }
    
    void Arkanoid::draw()
    {
        m_window.draw();
    }
}