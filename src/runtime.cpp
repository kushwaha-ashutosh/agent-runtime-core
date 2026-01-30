#include <iostream>
#include <string>

#include "runtime.h"
#include "agent.h"
#include "tools.h"

void Runtime::run(){
    std::cout<<"Runtime started"<<std::endl;

    Agent agent;

    for(int tick=1;tick<=MAX_STEPS;++tick){
        std::string action=agent.step(tick);

        std::cout<<"Agent says:"<<action<<std::endl;

        if(action=="search"){
            run_search_tool();
       }
        else if(action=="summarize"){
            run_summary_tool();
        }
        else if(action=="done"){
            break;
        }
    }
     
     std::cout<<"Runtime stopped"<<std::endl;
}
