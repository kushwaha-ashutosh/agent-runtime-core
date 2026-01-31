#pragma once
#include <string>

class Agent{
public:
    Agent();                
    std::string step();     
private:
    enum class State{
        Init,
        Summarize,
        Done
    };
    State state_;
};
