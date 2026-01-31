#include <iostream>
#include "telemetry.h"

void Telemetry::on_runtime_start(){
    std::cout<<"[Telemetry] Runtime started"<< std::endl;
}

void Telemetry::on_step(){
    step_count_++;
}

void Telemetry::on_tool_run(const std::string& tool_name){
    tool_run_count_++;
    std::cout<<"[Telemetry] Tool executed: "<<tool_name<<std::endl;
}

void Telemetry::on_runtime_stop(){
    std::cout<<"[Telemetry] Runtime stopped"<<std::endl;
    std::cout<<"[Telemetry] Steps executed:"<<step_count_<<std::endl;
    std::cout<<"[Telemetry] Tools executed:"<<tool_run_count_<<std::endl;
}
