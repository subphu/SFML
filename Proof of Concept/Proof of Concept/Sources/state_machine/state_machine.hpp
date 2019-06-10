#pragma once

#include <memory>
#include <stack>
#include "state.h"

using StateRef = std::shared_ptr<State>;

class StateMachine {
    
public:
    StateMachine(const StateRef& state);
    StateRef get_current_state() const;
    StateRef pop_state();
    void push_state(const StateRef& state);
    
private:
    std::stack<StateRef> stack;
    
};
