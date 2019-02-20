#ifndef ARK_MARKO_HH
#define ARK_MARKO_HH

#include "arko.hh"
#include <SDL2/SDL.h>

namespace ark
{
    class MenuObject : ArkObject
    {
    private:
        SDL_Rect m_area;
        
        
    public:
        const static char *MAIN_MENU_FONT = "";
        const static char *GAME_FONT = "";
    
        MenuObject(int,int,int,int);
        virtual ~MenuObject() = default;
        
        virtual void drawTo(SDL_Renderer*) const;
    };
}

#endif // ARK_MARKO_HH