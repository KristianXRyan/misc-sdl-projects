#ifndef ARK_GASTATE_HH
#define ARK_GASTATE_HH

#include "state.hh"
#include "statem.hh"

namespace ark
{
    class GameState : public ark::State
    {
    private:
        
    public:
        const static StateManager::StateType TYPE = StateManager::StateType::GAMESTATE;
        
        GameState(StateManager&);
        virtual ~GameState() = default;
    };
}

#endif // ARK_GASTATE_HH