#include "arko.hh"

#include <SDL2/SDL.h>

namespace ark
{
    ArkObject::ArkObject(int x, int y) 
        : m_position({ x, y })
    {

    }

    ArkObject::~ArkObject()
    {

    }

    void ArkObject::drawTo(SDL_Renderer *canvas) const
    {

    }
}