#include <iostream>

using namespace std;

std::string agent_step(int step){
    if(step==1){
        return"search";
    }
    if(step==2){
        return "summarize";

    }
    return "done";
}