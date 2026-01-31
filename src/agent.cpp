#include "agent.h"

Agent::Agent() : state_(State::Init){}

std::string Agent::step(){
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
