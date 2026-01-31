#pragma once
#include <string>

class Telemetry{
public:
    void on_runtime_start();
    void on_step();
    void on_tool_run(const std::string& tool_name);
    void on_failure(const std::string& reason);
    void on_runtime_stop();

private:
    int step_count_=0;
    int tool_run_count_=0;
    bool failed_ = false;
};
