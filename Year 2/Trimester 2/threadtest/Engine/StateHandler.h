#ifndef STATEHANDLER_H
#define STATEHANDLER_H

#include <string>
#include <map>
#include <iostream>

class StateHandler
{
    protected:
    std::map<int, std::string> States;
    int currentState;

    public:
        void AddState(std::string);
        void RemoveState(std::string);
        void StateTransistion(std::string NewState);
        int GetTotalStates();
        std::string GetCurrentState();
        virtual void EventHandler() const = 0;
        virtual ~StateHandler();
};
#endif