# Agent Design — Agent Runtime Core

## 1. Purpose of the Agent

This document defines the design of a **single, concrete agent** used to exercise and validate the Agent Runtime.

The agent’s responsibility is intentionally simple:

- Search for PDF files modified in the last N days
- Generate a summary of the discovered filenames
- Terminate cleanly

The agent exists to demonstrate **controlled execution**, **state-driven logic**, and **runtime supervision**, not AI sophistication.

---

## 2. Definition of an Agent

Within this project, an agent is defined as:

- A **passive state machine**
- Executed step-by-step by the runtime
- Capable of requesting predefined tools
- Incapable of controlling execution or resources

An agent does **not**:
- Run loops
- Spawn threads
- Call operating system APIs
- Execute tools directly

All execution is mediated by the runtime.

---

## 3. Agent State Model

The agent operates using a fixed set of states.

### Allowed States

1. `Init`  
2. `RequestFileSearch`  
3. `ProcessFileResults`  
4. `RequestSummary`  
5. `Completed`  
6. `Failed`  

No additional states are permitted.

States `Completed` and `Failed` are **terminal states**.

---

## 4. Agent Context

The agent maintains a minimal context required for decision-making.

### Stored Data

- Discovered file list
- Generated summary text
- Failure reason (if any)

The agent context:
- Is read-only during decision-making
- Is updated only by the runtime after tool execution

---

## 5. Allowed Tools

The agent is restricted to the following tools:

### FileSearchTool
- Input: directory, file extension, modified time window
- Output: list of file paths

### TextSummaryTool
- Input: list of filenames
- Output: summary string

If the agent requests a tool outside this list, execution is terminated by the runtime.

---

## 6. State-by-State Behavior

This section defines the exact logic executed during `AgentInstance::Step()`.

### State: Init
**Behavior**
- Prepare initial execution

**Next Action**
- Transition to `RequestFileSearch`
- Return a tool request for `FileSearchTool`

---

### State: RequestFileSearch
**Behavior**
- Await file search results from runtime

**Next Action**
- Runtime populates file list in context
- Transition to `ProcessFileResults`

---

### State: ProcessFileResults
**Decision Logic**
- If no files are found:
  - Transition to `Completed`
- If files are found:
  - Transition to `RequestSummary`

**Next Action**
- No tool execution
- State transition only

---

### State: RequestSummary
**Behavior**
- Request filename summarization

**Next Action**
- Return a tool request for `TextSummaryTool`
- Runtime stores summary in context
- Transition to `Completed`

---

### State: Completed
**Behavior**
- Signal successful completion
- No further execution permitted

This is a terminal state.

---

### State: Failed
**Behavior**
- Record failure reason
- Signal failure to runtime
- No further execution permitted

This is a terminal state.

---

## 7. Termination Rules

The agent must terminate execution when:

- State transitions to `Completed`
- State transitions to `Failed`
- Runtime cancels execution
- Runtime policy limits are exceeded

The agent never decides to continue execution autonomously.

---

## 8. Explicit Non-Behaviors

The following behaviors are explicitly forbidden:

- Infinite loops inside `Step()`
- Blocking or sleeping
- Direct filesystem access
- Dynamic tool discovery
- Tool-to-tool invocation

Violation of these rules results in immediate termination.

---

## 9. Implementation Guidance

When implementing this agent:

1. Define the `AgentState` enum
2. Define the `AgentContext` structure
3. Implement `AgentInstance::Step()` as a switch on state
4. Return exactly one result per step:
   - ToolRequest
   - Completed
   - Failed

No other execution model is permitted.

---

## 10. Design Rationale

This agent design intentionally prioritizes:

- Determinism over autonomy
- Observability over flexibility
- Runtime control over agent freedom

This aligns with platform-level engineering principles and enables safe evolution toward sandboxed and service-based execution models.

---

## 11. Summary

This agent is a minimal, deterministic state machine designed to validate the correctness of the Agent Runtime.

By enforcing strict state transitions, explicit tool usage, and runtime-controlled execution, the agent demonstrates how intelligent behavior can be safely composed within a platform environment.