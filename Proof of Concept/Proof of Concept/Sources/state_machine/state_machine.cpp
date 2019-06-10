#include "state_machine.hpp"
#include "state.h"

StateMachine::StateMachine(const StateRef& initialState) {
    push_state(initialState);
}

StateRef StateMachine::get_current_state() const {
    return stack.top();
}

StateRef StateMachine::pop_state() {
    auto state = get_current_state();
    stack.pop();
    return state;
}

void StateMachine::push_state(const StateRef& state) {
    stack.emplace(state);
}
