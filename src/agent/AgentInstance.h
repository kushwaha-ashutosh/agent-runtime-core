#pragma once
#include <string>

class AgentInstance{
public:
    AgentInstance();                
    std::string step();     
private:
    enum class State{
        Init,
        Summarize,
        Done
    };
    State state_;
};
