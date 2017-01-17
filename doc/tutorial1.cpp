#include <iostream>

#include "StateMachine.hpp"

class ExampleMachine : public StateMachine
{
#undef thisMachine
#define thisMachine machine<ExampleMachine>()
private:
    int _min, _max;
    int _currentValue;

    void everytime1()
    {
        std::cout << ((float)_currentValue) << " ";
    }

    beginState(increasing)
    {
        //increase until reach max, go decreasing state
        if (thisMachine->_currentValue >= thisMachine->_max)
            thisMachine->setStateI(decreasing);
        else
            ++ thisMachine->_currentValue;
    }
    endState

    beginState(decreasing)
    {
        //decrease until reach max, go increasing state
        if (thisMachine->_currentValue <= thisMachine->_min)
            thisMachine->setStateI(increasing);
        else
            -- thisMachine->_currentValue;
    }
    endState

public:
    ExampleMachine(int value = 0, int min = 0, int max = 9) :
        _min(min),
        _max(max),
        _currentValue(value)
    {
        setState(increasing);
    }
};

int main()
{
    ExampleMachine machine(2, 1, 7);
    for (int i = 0; i < 20; ++ i)
        machine.update();
}
