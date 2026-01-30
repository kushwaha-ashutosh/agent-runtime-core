#include <iostream>
#include <string>

#include "runtime.h"
#include "agent.h"
#include "tools.h"

void run_runtime() {
    std::cout<<"Runtime started"<<std::endl;

    for (int tick = 1; ; ++tick) {
        std::string action=agent_step(tick);

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
