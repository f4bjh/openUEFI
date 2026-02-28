# Execution Model

## 1. CPU Modes

Describe:
- Privilege levels
- Transition model
- Interrupt handling

## 2. Memory Model

- Address spaces
- MMU configuration
- Isolation model

## 3. Concurrency Model

- Single core vs SMP
- Scheduling strategy
- Interrupt vs polling

## 4. Microkernel Model

### 4.1. Microkernel state

Here is a table of microkernel and the conditions to move to another state.
Note : microkernel is allowed to move to next state if conditions are met, and if current state is the one specified in this table.
Else, error should be reported to the caller.

| Current state                 | Next state                    | Conditions                                        |
| ----------------------------- | ----------------------------- | ------------------------------------------------- |
| MUKERNEL_NOT_INITIALISED      | MUKERNEL_INITIALISED          | if basic hw initialisation succeed                |
| MUKERNEL_INITIALISED          | MUKERNEL_INTERFACE_REGISTERED | if shim and sentinel registers correctly          |
| MUKERNEL_INTERFACE_REGISTERED | MUKERNEL_STARTED              | if shim and sentinel intialisation succeed (+tbd) |
| MUKERNEL_STARTED              |  tbd                          |                                                   |
| MUKERNEL_STOPPED              |  tbd                          |                                                   |


