#ifndef ARK_GAMEOBJECT_HH
#define ARK_GAMEOBJECT_HH

#include "arko.hh"

#include <SDL2/SDL.h>

namespace ark
{
    class GameObject : public ArkObject
    {
    private:
        
    public:
        GameObject(int, int, int, int);
        virtual ~GameObject() = default;
        
        virtual void drawTo(SDL_Renderer*) const;
    };
}

#endif // ARK_GAMEOBJECT_HH