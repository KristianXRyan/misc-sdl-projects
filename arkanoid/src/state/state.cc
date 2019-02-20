#include "state/state.hh"

namespace ark
{
    State::State(ark::StateManager &sm)
        : m_sm(&sm)
    {
    }
    
    ark::StateManager* State::getSM() const
    {
        return m_sm;
    }
}