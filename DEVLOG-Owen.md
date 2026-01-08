# Dev Log:

This document must be updated daily every time you finish a work session.

## Owen Shi

### 2026-01-06 - Setting Up + Forking Server Work

Init'd the final project repository with boilerplate files and spent some time making a convenitent
and robust makefile. Also finished up and tested a basic forking server + clients that connect with
each other. Added in PROPOSAL.md and also updated README.md with group name, compilation instructions, etc.

### 2026-01-07 - Starting tournament bracket logic.

Start work on brackets. Assigned each client a specific ID to communicate with
the server. Need to figure out how the server will communicate with each, etc. Researched
how to share variables and datatypes between clients (will probably have to used
shared memory and semaphores?). Theory: Shared memory on the computer running
the server so all processes can get "global variables."
