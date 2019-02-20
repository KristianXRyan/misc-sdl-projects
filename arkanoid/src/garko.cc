#include "garko.hh"

namespace ark
{
    GameObject::GameObject(int x, int y, int w, int h)
        : ArkObject(x, y, w, h)
    {
    }
    
    void GameObject::drawTo(SDL_Renderer *canvas) const
    {
    
    }
}