#ifndef ARK_STATE_HH
#define ARK_STATE_HH

#include <vector>
#include <memory>

#include "arko.hh"

namespace ark
{
    class StateManager;
    class State
    {
    private:
        ark::StateManager *m_sm;
        std::vector<std::unique_ptr<ark::ArkObject>> m_objects; 
        
    public:
        State(ark::StateManager &);
        virtual ~State() = default;
        
        // getters
        ark::StateManager* getSM() const;
        
        // setters
        void addArkObject(ArkObject &);
    };
}

#endif // ARK_STATE_HH