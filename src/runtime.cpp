#include <iostream>
#include <string>
#include <vector>

#include "runtime.h"
#include "agent.h"
#include "tools.h"

void Runtime::run(){
    std::cout<<"Runtime started"<<std::endl;

    Agent agent;
    std::vector<Tool*> tools;
    SearchTool search_tool;
    SummaryTool summary_tool;

    tools.push_back(&search_tool);
    tools.push_back(&summary_tool);

    for(int tick=1;tick<=MAX_STEPS;++tick){
        std::string action=agent.step();

        std::cout<<"Agent says:"<<action<<std::endl;

         if(action=="done"){
            break;
        }
            
        for(Tool* tool:tools){
            if(tool->name()==action){
                tool->run();
                break;
            }
        }
    }
     
     std::cout<<"Runtime stopped"<<std::endl;
}
