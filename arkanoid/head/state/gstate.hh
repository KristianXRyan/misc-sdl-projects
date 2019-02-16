#ifndef ARK_GASTATE_HH
#define ARK_GASTATE_HH

#include <vector>

#include "state.hh"
#include "statem.hh"

#include "arko.hh"

namespace ark
{
    class GameState : public ark::State
    {
    private:
        // menu object
        // paddle, game objects
        std::vector<ark::ArkObject> m_objects; 
        
    public:
        const static StateManager::StateType TYPE = StateManager::StateType::GAMESTATE;
        
        GameState(StateManager&);
        ~GameState() = default;
    };
}

#endif // ARK_GASTATE_HH