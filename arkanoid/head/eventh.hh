#ifndef ARK_EVENT_HH
#define ARK_EVENT_HH

#include <SDL2/SDL.h>

namespace ark
{

    class EventHandler
    {
    private:
        SDL_Event m_event;
        
        bool m_playerRequestingClose;
        
    public:
        EventHandler();
        ~EventHandler();
    
        bool isPlayerRequestingClose() const;
        
        void listen();
    };
}

#endif // ARK_EVENT_HH