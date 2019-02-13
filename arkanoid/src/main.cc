#include <iostream>

#include "config.hh"
#include "ark.hh"

#include <SDL2/SDL.h>

int main(int argc, char **argv)
{
    ark::Arkanoid game;
    int returnCode = 0;
    
    try
    {
        game.initGraphics();
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << '\n';
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error initializing SDL",
            e.what(), NULL);
        returnCode = -1;
    }
    
    if(returnCode == 0)
        game.start();
    
    return returnCode;
}