#include "win.hh"

#include <stdexcept>

namespace ark
{
    Window::Window(const std::string &title, unsigned int w, unsigned int h)
        : m_title(title),m_width(w),m_height(h)
    {
    }
    
    Window::~Window()
    {
        SDL_DestroyRenderer(m_canvas);
        SDL_DestroyWindow(m_gWindow);
    }
    
    /* inits SDL window and canvas */ 
    void Window::show() 
    {
        m_gWindow = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_ALLOW_HIGHDPI);
            
        if(m_gWindow == NULL)
            throw std::runtime_error(std::string("Could not initialize Window ") +
                SDL_GetError());
                
        m_canvas = SDL_CreateRenderer(m_gWindow, -1, SDL_RENDERER_ACCELERATED);
        
        if(m_canvas == NULL)
            throw std::runtime_error(std::string("Could not create renderer ") +
                SDL_GetError());
    }
    
    void Window::draw()
    {
        SDL_SetRenderDrawColor(m_canvas, 0, 0, 0, 0xFF);
        SDL_RenderClear(m_canvas);
        
        SDL_RenderPresent(m_canvas);
    }
}