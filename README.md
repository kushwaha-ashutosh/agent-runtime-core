# Agent Runtime Core (C++)

A minimal, production-style **agent execution runtime** written in C++.  
This project focuses on **execution control, system design, and reliability**, not model intelligence.

It demonstrates how an agent can be executed safely under a runtime that enforces policies, invokes tools through a clean interface, records telemetry, and handles failures gracefully.

---

## High-Level Overview

The system is composed of four core components:

- **AgentRuntime** – Owns the execution loop, enforces safety policies, and coordinates components
- **AgentInstance** – A state-machine-based agent that decides the next action
- **Tool Interface** – Polymorphic interface for runtime-approved actions
- **Telemetry** – Passive observer for execution metrics and failure reporting

The agent never controls execution directly and never invokes tools on its own.

---

## Architecture Diagram (Conceptual)
```
main
└── AgentRuntime
    ├── AgentInstance (state machine)
    ├── Tool registry (polymorphic)
    ├── Telemetry (observer)
    ├── Safety policy (max steps)
    └── Failure handling
```

---

## Execution Model

1. `main` initializes the runtime
2. The runtime enters a controlled execution loop
3. The agent returns the next requested action
4. The runtime selects and executes the corresponding tool
5. Telemetry records steps, tool usage, and failures
6. Execution stops on completion, policy violation, or error

The runtime always remains in control.

---

## Key Design Decisions

- **Runtime-controlled execution** prevents runaway agent behavior
- **State-machine-based agent** ensures predictable and testable logic
- **Polymorphic tool interface** allows extensibility without runtime changes
- **Telemetry as observer** avoids side effects on execution logic
- **Failure-first design** treats errors as structured signals, not crashes

---

## Failure Handling

The runtime safely handles:

- Requests for non-existent tools
- Tool execution failures (exceptions)
- Early termination with full telemetry reporting

Failures result in **deterministic shutdown**, not undefined behavior.

---

## Project Structure
```
agent-runtime-core/
│
├── docs/
│   ├── architecture.md
│   ├── execution-model.md
│   ├── tradeoffs.md
│   └── failure-scenarios.md
│
├── src/
│   ├── main.cpp
│   │
│   ├── runtime/
│   │   ├── AgentRuntime.h
│   │   ├── AgentRuntime.cpp
│   │   ├── Telemetry.h
│   │   └── Telemetry.cpp
│   │
│   ├── agent/
│   │   ├── AgentInstance.h
│   │   └── AgentInstance.cpp
│   │
│   ├── tools/
│   │   ├── Tool.h
│   │   ├── SearchTool.h / .cpp
│   │   └── SummaryTool.h / .cpp
│
├── CMakeLists.txt
├── README.md
└── LICENSE
```

---

## Build & Run (GCC / Clang)
```bash
g++ -std=c++17 \
    src/main.cpp \
    src/runtime/AgentRuntime.cpp \
    src/runtime/Telemetry.cpp \
    src/agent/AgentInstance.cpp \
    src/tools/SearchTool.cpp \
    src/tools/SummaryTool.cpp \
    -o agent-runtime

./agent-runtime
```

---

## Build & Run (Windows – MSVC)

This project supports building on Windows using CMake and MSVC.
```bash
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release
```

The executable will be generated at:
```
build/Release/agent-runtime.exe
```

---

## Scope & Intent

This project intentionally focuses on execution architecture, not AI model implementation.

Advanced features such as concurrency, async execution, dynamic loading, or scheduling were deliberately deferred to preserve clarity, correctness, and observability.

---

## What This Project Demonstrates

- Systems-level C++ design
- Execution control and safety enforcement
- State machines
- Polymorphism and clean interfaces
- Telemetry and observability
- Graceful failure handling
- Incremental refactoring without behavior regression

---

## License

MIT License