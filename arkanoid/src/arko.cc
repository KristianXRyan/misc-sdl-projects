#include "arko.hh"

#include <SDL2/SDL.h>

namespace ark
{
    ArkObject::ArkObject(int x, int y, int w, int h) 
        : m_area({ x, y, w, h })
    {
    }
    

    int ArkObject::getx() const
    {
        return m_area.x;
    }
    
    int  ArkObject::gety() const
    {
        return m_area.y;
    }
    
    int  ArkObject::getWidth() const
    {
        return m_area.w;
    }
    
    int  ArkObject::getHeight() const
    {
        return m_area.h;
    }
}