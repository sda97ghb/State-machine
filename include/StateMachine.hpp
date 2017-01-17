#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <stack>

class StateMachine
{
protected:
    class State
    {
    private:
        StateMachine* _machine;
    public:
        State() = delete;
        State(StateMachine* machine) :
            _machine(machine)
        {}
        virtual void operator() () = 0;
        virtual ~State() {}
        template <typename StateMachineType>
        StateMachineType* machine()
        {
            return static_cast<StateMachineType*>(_machine);
        }
    };

    std::stack<State*> _statesStack;

    virtual void everytime1()
    {}
    virtual void everytime2()
    {}

    template <typename StateName>
    void pushState_(StateMachine* machine)
    {
        _statesStack.push(new StateName(machine));
    }
#define pushState(stateName) pushState_<stateName>(this)
#define pushStateI(stateName) pushState_<stateName>(thisMachine)

    void popState()
    {
        State* topState = _statesStack.top();
        if (topState)
            delete topState;
        _statesStack.pop();
    }

    void clearStatesStack()
    {
        while (!_statesStack.empty())
        {
            State* topState = _statesStack.top();
            if (topState)
                delete topState;
            _statesStack.pop();
        }
    }

    template <typename StateName>
    void setState_(StateMachine* machine)
    {
        clearStatesStack();
        _statesStack.push(new StateName(machine));
    }
#define setState(stateName) setState_<stateName>(this)
#define setStateI(stateName) setState_<stateName>(thisMachine)

public:
    void update()
    {
        everytime1();
        if (!_statesStack.empty())
        {
            State* currentState = _statesStack.top();
            (*currentState)();
        }
        everytime2();
    }
};

#define beginState(stateName)               \
    friend class stateName;                 \
    class stateName : public State          \
    {                                       \
    public:                                 \
        stateName() = delete;               \
        stateName(StateMachine* machine) :  \
            State(machine)                  \
        {}                                  \
        void operator() ()
#define endState };

#endif // STATEMACHINE_H
