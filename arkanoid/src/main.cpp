#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <thread>
#include <chrono>

extern "C" {
#include <SDL2/SDL.h>
}

#include "paddle.hpp"

struct
{
    SDL_Window   *window;
    SDL_Renderer *renderer;
    SDL_Event     event;
} SDL_Object;

struct
{
    std::vector<ark::Paddle> paddles;
} gameObject;

struct
{
    unsigned int frames = 0;
} gameData;

static bool getInput()
{
    bool userClose = false;
    
    while(SDL_PollEvent(&SDL_Object.event))
    {
        switch(SDL_Object.event.type)
        {
        case SDL_QUIT:
            userClose = true;
            break;

        default:
            break;
        }
    }

    return userClose;
}

static void render()
{
    SDL_SetRenderDrawColor(SDL_Object.renderer, 0, 0, 0, 255);
    SDL_RenderClear(SDL_Object.renderer);


    SDL_RenderPresent(SDL_Object.renderer);
}

static void run()
{
    constexpr float FRAME_TIME = 1000.0f / 60.0f;
    
    bool run = true;

    using namespace std;
    using namespace std::chrono;

    system_clock::time_point startFrameTime;
	duration<float> frameRenderTime;

    while(run)
    {
        startFrameTime = system_clock::now();
        
        // user input (returns if the user is trying to exit)
        run = !getInput();
        
        // simulation

        // render
        render();

        if(gameData.frames == 60u)
            gameData.frames = 0u;
        
        // framerate and simulation control
		frameRenderTime = system_clock::now() - startFrameTime;
		if (FRAME_TIME > frameRenderTime.count())
		{
            std::cout << "Run\n";
			duration<double, milli> waitTimeMS(FRAME_TIME - frameRenderTime.count());
			milliseconds deltaDuration = duration_cast<milliseconds>(waitTimeMS);
            this_thread::sleep_for(deltaDuration);
            gameData.frames++;
		}

    }
}

static void init()
{
    std::string errorMsg = "SDL runtime error: ";
    
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO))
    {
        errorMsg += SDL_GetError();
        throw std::runtime_error(errorMsg);
    }

    SDL_Object.window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                     1200, 600, SDL_WINDOW_ALLOW_HIGHDPI);

    if(SDL_Object.window == nullptr)
    {
        errorMsg += SDL_GetError();
        throw std::runtime_error(errorMsg);
    }

    SDL_Object.renderer = SDL_CreateRenderer(SDL_Object.window, -1, SDL_RENDERER_ACCELERATED);

    if(SDL_Object.renderer == nullptr)
    {
        errorMsg += SDL_GetError();
        throw std::runtime_error(errorMsg);
    }   
}

static void destroy()
{
    SDL_DestroyWindow(SDL_Object.window);
    SDL_DestroyRenderer(SDL_Object.renderer);

    SDL_Quit();
}

int main(int argc, char **argv)
{
    int exitCode = 0;
    
    try
    {
        init();
        run();
    }
    catch(std::runtime_error &e)
    {
        std::cerr << e.what() << '\n';
        exitCode = 1;
    }

    destroy();
    
    return exitCode;
}
