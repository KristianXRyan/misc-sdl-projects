#ifndef PONG_ENGINE_INTERFACE
#define PONG_ENGINE_INTERFACE

#include "po.hpp"

#include <vector>
#include <memory>

namespace p
{
    class State
    {
    private:
        std::vector<std::unique_ptr<p::Object>> _objects;
        
    public:
        virtual void Run() = 0;

        
    };
    
    bool Init();

    void Quit();
}

#endif // PONG_ENGINE_INTERFACE
