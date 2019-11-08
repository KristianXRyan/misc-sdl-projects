#include "eng.hpp"

#include <iostream>
#include <SDL2/SDL_gpu.h>

struct sdl_data
{
    GPU_Target *window;
    SDL_Event    event;
};

static sdl_data sd;

static std::vector<p::State> states;

bool p::Init()
{
    sd.window = GPU_Init(800, 600, GPU_DEFAULT_INIT_FLAGS);

    if(sd.window == nullptr)
    {
        std::cerr << "SDL: " << SDL_GetError() << '\n';
        return false;
    }

    return true;
}

void p::Quit()
{
    GPU_Quit();
}
