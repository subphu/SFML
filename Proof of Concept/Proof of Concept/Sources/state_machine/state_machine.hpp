#pragma once

#include <memory>
#include <stack>
#include "state.h"

using StateRef = std::shared_ptr<State>;

class StateMachine {
    
public:
    StateMachine(const StateRef& state);
    
    StateRef getCurrentState() const;
    StateRef popState();
    
    void pushState(const StateRef& state);
    
private:
    std::stack<StateRef> stack;
    
};
