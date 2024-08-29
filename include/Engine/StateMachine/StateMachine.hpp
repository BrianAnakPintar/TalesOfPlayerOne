#ifndef GAME_UI_H
#define GAME_UI_H

#include "State.hpp"
#include <memory>
#include <stack>

typedef std::unique_ptr<State> StateRef;

// Handles the current state of the game. (i.e. Menu screen, game screen, etc.)
class StateMachine {
private:
    std::stack<StateRef> states;
    StateRef newState;
    bool isRemoving;
    bool isAdding;
    bool isReplacing;
public:
    void AddState(StateRef newState, bool isReplacing = true);
    void RemoveState();

    void ProcessStateChanges();
    StateRef& GetActiveState();
};

#endif // !GAME_UI_H
