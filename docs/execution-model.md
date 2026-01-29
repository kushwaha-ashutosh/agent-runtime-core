# Execution Model — Agent Runtime Core

## 1. Overview

This document describes **how agents are executed**, step-by-step, within the Agent Runtime.

The execution model is designed to:

- Maintain strict runtime control
- Prevent uncontrolled or infinite execution
- Enable deterministic behavior
- Support cancellation, failure handling, and observability

At no point does an agent execute independently or control system resources.

---

## 2. Core Execution Principle

> **Agents do not run — they are advanced by the runtime.**

Agents are modeled as **passive state machines**.

The runtime explicitly decides:

- When an agent executes
- How much work it can perform
- When it must stop

This mirrors operating system scheduling principles.

---

## 3. Agent as a State Machine

Each agent implements a `Step()` function that represents **one bounded unit of work**.

### Characteristics

- No loops inside `Step()`
- No blocking calls
- No direct OS access
- No thread ownership

The agent may:

- Request a tool
- Signal completion
- Signal failure

---

## 4. Runtime Tick Model

Execution is driven by the runtime via **ticks**.

### High-level flow
```
while runtime is active:
    Scheduler selects next agent
    Runtime advances agent by one step
    Runtime enforces policies
    Runtime records telemetry
```

Each tick advances **at most one agent step**.

This ensures:

- Fairness
- Predictable latency
- Controlled resource usage

---

## 5. Detailed Execution Flow

### Step 1: Agent Selection

The scheduler selects an eligible agent based on:

- Execution state
- Fairness
- Policy constraints

Agents that are:

- Completed
- Failed
- Cancelled

are excluded.

---

### Step 2: Agent Step Invocation

The runtime invokes:
```
AgentInstance::Step()
```

This method:

- Evaluates internal state
- Determines the next logical action
- Returns an execution result

---

### Step 3: Agent Step Result

An agent step may return one of the following:

- **ToolRequest**
- **Completed**
- **Failed**

Agents cannot directly execute tools.

---

### Step 4: Policy Validation

Before any action is executed, the runtime consults the PolicyEngine to validate:

- Execution step count
- Elapsed execution time
- Tool permissions
- Agent state validity

If validation fails:

- The agent is terminated
- A failure reason is recorded

---

### Step 5: Tool Execution

If the step result is a tool request:

- The runtime invokes the tool
- Execution is supervised and bounded
- Failures are isolated

Tools:

- Perform one specific action
- Cannot invoke other tools
- Cannot control execution flow

---

### Step 6: Telemetry Recording

After each step:

- Execution time is recorded
- Tool usage is logged
- Failures are categorized

Telemetry is written **regardless of success or failure**.

---

### Step 7: Scheduler Advancement

The scheduler advances to the next agent.

This continues until:

- All agents complete
- Runtime shutdown is requested

---

## 6. Execution Limits

To prevent runaway behavior, the runtime enforces:

- Maximum step count per agent
- Maximum wall-clock execution time
- Bounded tool execution time

Violations result in **controlled termination**.

---

## 7. Cancellation and Termination

Agents may be terminated due to:

- Policy violation
- Tool failure
- Explicit cancellation
- Runtime shutdown

Termination is:

- Immediate
- Safe
- Observable

Partial state is discarded unless explicitly persisted.

---

## 8. Failure Handling Model

Failures are treated as first-class outcomes.

Failure isolation guarantees:

- Agent failure does not crash the runtime
- Tool failure does not corrupt agent state
- Other agents continue unaffected

Failure reasons are explicitly recorded.

---

## 9. Determinism Guarantees

The execution model guarantees:

- Bounded execution per step
- Predictable scheduling behavior
- Reproducible execution paths given identical inputs

Non-deterministic behavior is intentionally minimized.

---

## 10. Why This Model Was Chosen

This execution model:

- Simplifies reasoning about correctness
- Enables strong observability
- Aligns with OS and platform engineering principles
- Scales from in-process execution to service-based deployment

Alternative models (free-running threads, async-only execution) were rejected due to poor observability and weak execution control.

---

## 11. Summary

The Agent Runtime executes agents as **controlled, deterministic state machines**, not autonomous programs.

By centralizing execution control within the runtime, the system ensures safety, reliability, and debuggability — properties required for platform-level integration.