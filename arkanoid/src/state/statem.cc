#include "state/statem.hh"

#include "state/mstate.hh"

namespace ark
{
    StateManager::StateManager()
        : m_currentState(0)
    {
        m_gameStates.push_back(std::make_unique<ark::MenuState>(*this));
    }
}