# Security model

## 0. Terminology

*Trusted Computing Base*

The Trusted Computing Base (TCB) is the minimal set of hardware and software components whose correct operation is strictly required to enforce the security invariants defined by openUEFI.

The TCB explicitly includes the openUEFI microkernel and the underlying hardware mechanisms responsible for privilege enforcement and memory protection, including CPU privilege levels and paging mechanisms.

Physical memory is assumed to operate correctly and is considered part of the trusted execution substrate under the defined threat model.

Any defect, vulnerability, or compromise within the TCB may directly violate one or more security invariants.

Components outside the TCB are considered untrusted by design. The system must enforce strict privilege confinement such that no component outside the TCB can obtain privileges beyond those explicitly granted by the security policy.

*Microkernel*

The Microkernel is the minimal privileged software component executing at the highest CPU privilege level supported by the underlying architecture.

It forms the core of the Trusted Computing Base (TCB).

The Microkernel is responsible exclusively for:

-Enforcement of architectural privilege separation,
-Enforcement of memory isolation through controlled page table management,
-Controlled transitions between privilege levels,
-Enforcement of defined security invariants.

The Microkernel retains exclusive control over page tables and memory protection mechanisms.

The Microkernel remains resident throughout the system lifetime and does not relinquish ultimate authority over execution control.

The Microkernel does not implement multitasking, device drivers, general-purpose operating system services, or full firmware services.

*Sentinel*

The Sentinel is a software component executed under the control of the Microkernel at a lower CPU privilege level.

The Sentinel is responsible for implementing the system boot policy, including the selection and validation of payloads to be executed.

The Sentinel operates within an execution environment enforced by the Microkernel and interacts with system resources exclusively through Microkernel-provided interfaces.

The Sentinel is not part of the Trusted Computing Base.

*Payload*

A Payload is an executable software component loaded and launched by the Sentinel under the control of the Microkernel.

The Payload executes outside the Trusted Computing Base and is considered untrusted by design.

The Payload executes in an execution environment enforced by the Microkernel and does not interact with the Microkernel through runtime interfaces.

Examples of payloads include, but are not limited to:
- a bootloader,
- an operating system,
- a hypervisor,
- or another execution environment such as a language runtime.
_A Runtime is a software environment responsible for executing application programs, typically providing services such as memory management, scheduling, or language execution support._

*Measurement*
A Measurement is a cryptographic hash value computed over a software component prior to its execution.

Measurements are performed by the Microkernel and recorded in the Measurement Log to provide a verifiable record of the software components executed during system startup.

*Measurement Log*
A Measurement Log is a secure, tamper-evident ledger maintained by the Microkernel that records the cryptographic measurements of all critical software components executed during system startup. Each entry corresponds to a Measurement, defined as a cryptographic hash of a software component computed prior to its execution. The Measurement Log provides a verifiable record of the system’s execution history and underpins the chain of trust from the Microkernel to all loaded components.

The Measurement Log enforces the following security properties:

- Append-only structure : Entries are never removed or modified once recorded. This guarantees chronological integrity and ensures that any attempt at tampering with the execution history is detectable.
- Exclusive maintenance by the Microkernel. Only the Microkernel is authorized to write entries to the log. This limits the Trusted Computing Base (TCB) and prevents any untrusted or privileged runtime component from altering the system’s integrity record.
- Restricted read access : The log is readable solely by the Sentinel, ensuring that sensitive measurement data is protected from all other software while still allowing verification of the system’s integrity.
- Saturation handling : The Measurement Log is dimensioned to contain exactly all expected Measurements for a single system boot. In the event that the log reaches its capacity or a Measurement fails (e.g., a signature verification fails), the Microkernel halts the boot process, preventing execution of unverified code.
- Verification of Payloads via digital signature : Instead of comparing against a fixed hash, each Payload is verified using a cryptographic signature. The Microkernel validates the signature against a trusted public key embedded in the TCB. This approach eliminates the need for a static database of allowed hashes, supports secure updates to the Payload, and ensures that only authenticated software is executed.

Justification: This design guarantees that the Measurement Log remains a complete, verifiable, and secure record of all critical software executed during boot. The append-only structure, exclusive maintenance, and restricted read access protect against tampering, while the use of signatures ensures flexible and secure update of Payloads without compromising the chain of trust. Saturation handling via boot halt ensures that no unverified component is ever executed.

*Measured Boot*
Measured Boot refers to the process of system startup in which each critical stage of the boot sequence is evaluated and recorded through cryptographic proofs, thereby ensuring the integrity and traceability of the startup sequence. These proofs are immutably logged in the Measurement Log, enabling trusted components to verify the validity of each boot element.

The fundamental purpose of Measured Boot is to provide a verifiable chain of trust, from the microkernel to the payload (bootloader, OS, hypervisor, or runtime), so as to detect any unauthorized modification and maintain system security throughout the boot process.

Key characteristics:
- Cryptographic traceability: each boot stage is measured using digests or signatures.
- Reliability and immutability: measurements are append-only and protected against tampering.
- Independent verification basis: allows trusted components, such as the Sentinel, to validate system integrity without relying on untrusted components.

## 1. Security Goals

This section defines the security properties that the openUEFI architecture aims to guarantee.

The design follows a minimalist security philosophy: the trusted computing base is intentionally kept small, and untrusted components are confined by design. Security decisions are explicit, deterministic, and observable.

The goals described in this section define what the system guarantees, not how those guarantees are implemented. The mechanisms enforcing these properties are described in later sections.

The security model is structured around three fundamental principles:

Execution Control — ensuring that only authorized code may execute.

Isolation — ensuring that executing code cannot exceed its assigned privileges.

Observability — ensuring that the boot process can be verified and audited.

### 1.1 Execution Control

The system must ensure that code execution during the boot process is strictly controlled and governed by explicit security policy decisions.

No code may be executed without explicit authorization. All transitions of execution during the boot process must be validated according to the system's security policy.

The integrity of the boot process must be preserved. The system must guarantee that the code being executed corresponds exactly to the code that has been authorized. Unauthorized modifications, substitutions, or injections of executable code must be detectable and preventable.

Security decisions governing the boot process must be taken by a clearly identified component responsible for enforcing boot policy. This ensures that the authority responsible for permitting execution is explicit and unambiguous.

Boot decisions must be deterministic for a given system state. Identical inputs and system conditions must lead to identical execution decisions. This deterministic behavior improves predictability and facilitates security analysis and auditing.

Execution authorization must be governed by an explicit security policy. The policy defines which code may be executed and under which conditions, ensuring that execution control remains transparent and verifiable.

### 1.2 Isolation

The system must ensure that code execution cannot compromise the integrity of the platform, even when that code has been authorized to run.

Authorized code must not automatically be considered trusted. Code that is permitted to execute must still operate within strictly defined privilege boundaries.

Payloads executed during the boot process are considered untrusted by design. The system must enforce isolation mechanisms that prevent payloads from exceeding their assigned privileges or interfering with critical components.

The integrity of the core system components must be preserved. In particular, components responsible for enforcing security decisions must be protected against modification or interference by executing payloads.

The trusted computing base must remain as small as possible. Minimizing the amount of code that must be trusted reduces the attack surface and improves the feasibility of auditing and verification.

### 1.3 Observability

The system must ensure that the boot process can be observed and verified.

The execution of critical components must be measurable in order to provide evidence of the system state during the boot process. Measurements must allow verification that the expected components have been executed.

The system must provide sufficient information to allow auditing of the boot process. An observer must be able to reconstruct and verify the sequence of execution decisions that occurred during system initialization.

Security decisions made during the boot process must be traceable. It must be possible to determine why a particular execution decision was made and which components were involved.

This observability property enables the verification of system integrity and supports security analysis and auditing.

## 2. Threat Model
## 3. Trusted Computing Base
## 4. Security Architecture
## 5. Isolation Model
## 6. Measured Boot
## 7. Boot Policy Enforcement
## 8. Security Invariants
## 9. Assumptions and Limitations
## 10. Open Questions
