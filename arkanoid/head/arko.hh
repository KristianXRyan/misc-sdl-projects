#ifndef ARKO_HH
#define ARKO_HH

#include <SDL2/SDL.h>

namespace ark
{
    class ArkObject
    {
    private:
        SDL_Rect m_area;
        
    public:
        ArkObject(int,int,int,int);
        virtual ~ArkObject() = default;
        
        virtual void drawTo(SDL_Renderer *) const = 0;
        
        // getters
        int getx() const;
        int gety() const;
        int getWidth() const;
        int getHeight() const;
    };

}
#endif // ARKO_HH