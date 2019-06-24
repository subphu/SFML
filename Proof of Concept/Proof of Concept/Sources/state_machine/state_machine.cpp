#include "state_machine.hpp"
#include "state.h"

StateMachine::StateMachine(const StateRef& initialState) {
    pushState(initialState);
}

StateRef StateMachine::getCurrentState() const {
    return stack.top();
}

StateRef StateMachine::popState() {
    auto state = getCurrentState();
    stack.pop();
    return state;
}

void StateMachine::pushState(const StateRef& state) {
    stack.emplace(state);
}
