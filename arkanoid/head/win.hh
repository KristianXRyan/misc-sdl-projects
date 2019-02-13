#ifndef ARK_WIN_HH
#define ARK_WIN_HH

#include <SDL2/SDL.h>

#include <string>

namespace ark
{
    class Window
    {
    private:
        // SDL structs
        SDL_Window *m_gWindow;
        SDL_Renderer *m_canvas;
        
        // window data
        std::string m_title;
        unsigned int m_width;
        unsigned int m_height;
        
    public:
        Window(const std::string&, unsigned int, unsigned int);
        ~Window();
        
        void show();
    };
}
#endif // ARK_WIN_HH