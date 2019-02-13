#include "eventh.hh"

namespace ark
{
    EventHandler::EventHandler()
        : m_playerRequestingClose(false)
    { 
    }
    
    EventHandler::~EventHandler()
    {
    }
    
    bool EventHandler::isPlayerRequestingClose() const
    {
        return m_playerRequestingClose;
    }    
    
    void EventHandler::listen()
    {
        while(SDL_PollEvent(&m_event))
        {
            switch(m_event.type)
            {
            case SDL_QUIT:
                m_playerRequestingClose = true;
                break;
            default:
                break;
            }
        }
    }
}