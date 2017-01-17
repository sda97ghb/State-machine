#include <iostream>

#include "StateMachine.hpp"

class ExampleStateMachine : public StateMachine
{
#undef thisMachine
#define thisMachine machine<ExampleStateMachine>()
private:
    int counter;
    std::string name;

    beginState(State1)
    {
        printMachine();
        std::cout << thisMachine->name << " state 1" << std::endl;
        thisMachine->counter ++;
        std::cout << "counter = " << thisMachine->counter << std::endl;
    }
    static void printMachine()
    {
        std::cout << "machine: ";
    }
    endState

    beginState(State2)
    {
        std::cout << "machine: " << thisMachine->name << " state 2" << std::endl;
    }
    endState

public:
    ExampleStateMachine(std::string iname) :
        counter(0),
        name(iname)
    {}

    void goState1()
    {
        State1::printMachine();
        clearStatesStack();
        pushState(State1);
    }
    void goState2()
    {
        clearStatesStack();
        pushState(State2);
    }
};

class Runner : public StateMachine
{
#undef thisMachine
#define thisMachine machine<Runner>()
private:
    int _value;
    int _min;
    int _max;

    void printValue()
    {
        std::cout << _value << " ";
//        std::cout << _value << std::endl;
    }

    void everytime1()
    {
        std::cout << std::endl;
    }

    beginState(increasing)
    {
        thisMachine->printValue();
        if (thisMachine->_value >= thisMachine->_max)
            thisMachine->setStateI(decreasing);
        else
            ++ thisMachine->_value;
    }
    endState

    beginState(decreasing)
    {
        thisMachine->printValue();
        if (thisMachine->_value <= thisMachine->_min)
            thisMachine->setStateI(increasing);
        else
            -- thisMachine->_value;
    }
    endState

public:
    Runner(int min = 0, int max = 9) :
        _value(0),
        _min(min),
        _max(max)
    {
        setState(increasing);
    }
};

int main()
{
    ExampleStateMachine machine1("m1");
    ExampleStateMachine machine2("m2");

    machine1.goState1();
    machine2.goState2();
    machine1.update();
    machine2.update();
    machine1.update();
    machine2.update();
    machine1.goState2();
    machine1.update();
    machine2.update();
    machine2.goState1();
    machine1.update();
    machine2.update();
    machine1.update();
    machine2.update();
    machine1.update();
    machine2.update();

    Runner runner;
    for (int i = 0; i < 30; ++ i)
        runner.update();

    return 0;
}
