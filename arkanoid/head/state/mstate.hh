#ifndef ARK_MSTATE_HH
#define ARK_MSTATE_HH

#include "state/state.hh"


namespace ark
{
    class StateManager;
    class MenuState : public State
    {
    private:
    
    public:
        MenuState(ark::StateManager &);
        virtual ~MenuState() = default;
    };
}

#endif // ARK_MSTATE_HH