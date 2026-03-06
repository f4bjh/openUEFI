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

1. Project Intent
2. Assumptions
3. Threat Model
4. Trusted Computing Base
5. Architectural Security Principles
6. Security Invariants
7. Compatibility Scope
8. Out of Scope
