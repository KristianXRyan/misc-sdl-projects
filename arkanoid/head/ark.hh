#ifndef ARK_ARK_HH
#define ARK_ARK_HH

#include "win.hh"
#include "eventh.hh"

namespace ark
{
    class Arkanoid
    {
    private:
        Window m_window;
        EventHandler m_eventHandler;
        
    public:
        Arkanoid();
        ~Arkanoid();
        
        void start();
        void initGraphics();
        
    private:
    
        void run();
        void update();
        void draw();
    };
}

#endif // ARK_ARK_HH