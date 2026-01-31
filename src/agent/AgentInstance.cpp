#include "AgentInstance.h"

AgentInstance::AgentInstance() : state_(State::Init){}

std::string AgentInstance::step(){
    if(state_==State::Init){
        state_=State::Summarize;
        return "search";
    }

    if(state_==State::Summarize){
        state_=State::Done;
        return "summarize";
    }

    return "done";
}

