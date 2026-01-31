#include <iostream>
#include <string>
#include <vector>
#include <exception>

#include "runtime.h"
#include "agent.h"
#include "tools.h"
#include "telemetry.h"

void Runtime::run(){
    Telemetry telemetry;
    telemetry.on_runtime_start();
    
    std::cout<<"Runtime started"<<std::endl;

    Agent agent;
    std::vector<Tool*> tools;
    SearchTool search_tool;
    SummaryTool summary_tool;

    tools.push_back(&search_tool);
    tools.push_back(&summary_tool);

    for(int tick=1;tick<=MAX_STEPS;++tick){
        telemetry.on_step();

        std::string action=agent.step();

        std::cout<<"Agent says:"<<action<<std::endl;

         if(action=="done"){
            break;
        }

        bool tool_found=false;
            
        for(Tool* tool:tools){
            if(tool->name()==action){
                tool_found=true;
                try{
                    tool->run();
                    telemetry.on_tool_run(tool->name());
                }catch(const std::exception& e){
                    telemetry.on_failure(e.what());
                    std::cout<<"Runtime stopping due to tool failure"<<std::endl;
                    telemetry.on_runtime_stop();
                    return;
                }
                break;
            }
        }

        if (!tool_found){
            telemetry.on_failure("Requested tool not found: "+action);
            std::cout<<"Runtime stopping due to missing tool" << std::endl;
            telemetry.on_runtime_stop();
            return;
        }
    }

    std::cout<<"Runtime stopped"<<std::endl;
    telemetry.on_runtime_stop();
}