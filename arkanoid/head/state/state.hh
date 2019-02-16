#ifndef ARK_STATE_HH
#define ARK_STATE_HH

namespace ark
{
    class StateManager;
    class State
    {
    private:
        ark::StateManager *m_sm;
        
    public:
        State(ark::StateManager &);
        ~State() = default;
    };
}

#endif // ARK_STATE_HH