#include <iostream>
#include <string>

#include "runtime.h"
#include "agent.h"
#include "tools.h"

void Runtime::run(){
    std::cout<<"Runtime started"<<std::endl;

    Agent agent;
    SearchTool search_tool;
    SummaryTool summary_tool;

    for(int tick=1;tick<=MAX_STEPS;++tick){
        std::string action=agent.step(tick);

        std::cout<<"Agent says:"<<action<<std::endl;

        if(action=="search"){
            search_tool.run();
       }
        else if(action=="summarize"){
            summary_tool.run();
        }
        else if(action=="done"){
            break;
        }
    }
     
     std::cout<<"Runtime stopped"<<std::endl;
}
