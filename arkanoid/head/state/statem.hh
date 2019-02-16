#ifndef ARK_STATEMAN_HH
#define ARK_STATEMAN_HH

#include <vector>
#include <memory>

#include "state.hh"

namespace ark
{
    class StateManager
    {
    private:
        
        
        unsigned int m_currentState;
        std::vector<std::unique_ptr<ark::State>> m_gameStates;
        
    public:
        enum class StateType
        {
            MENUSTATE,
            GAMESTATE
        };
    
        StateManager();
        ~StateManager() = default;
    };
}

#endif // ARK_STATEMAN_HH