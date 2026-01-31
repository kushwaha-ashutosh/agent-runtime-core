cmake_minimum_required(VERSION 3.16)

project(agent_runtime_core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(agent-runtime
    src/main.cpp
    src/runtime/AgentRuntime.cpp
    src/runtime/Telemetry.cpp
    src/agent/AgentInstance.cpp
    src/tools/SearchTool.cpp
    src/tools/SummaryTool.cpp
)

target_include_directories(agent-runtime PRIVATE
    src
    src/runtime
    src/agent
    src/tools
)
