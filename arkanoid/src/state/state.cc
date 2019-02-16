#include "state/state.hh"

namespace ark
{
    State::State(ark::StateManager &sm)
        : m_sm(&sm)
    {
    }
}