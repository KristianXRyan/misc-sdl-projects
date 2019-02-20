#ifndef ARK_ARK_HH
#define ARK_ARK_HH

#include "win.hh"
#include "eventh.hh"
#include "state/statem.hh"

namespace ark
{
    class Arkanoid
    {
    private:
        Window m_window;
        EventHandler m_eventHandler;
        StateManager m_sm;
        
    public:
        Arkanoid();
        ~Arkanoid();
        
        void start();
        void initGraphics();
        
    private:
    
        void run();
        void update();
        void draw();
        void tick();
    };
}

#endif // ARK_ARK_HH