# Dev Log:

This document must be updated daily every time you finish a work session.

## Owen Shi

### 2026-01-06 - Setting Up + Forking Server Work

Init'd the final project repository with boilerplate files and spent some time making a convenitent
and robust makefile. Also finished up and tested a basic forking server + clients that connect with
each other. Added in PROPOSAL.md and also updated README.md with group name, compilation instructions, etc.

(1.5 hour)

### 2026-01-07 - Finished forking server. Starting tournament bracket logic.

Start work on brackets. Assigned each client a specific ID to communicate with
the server. Need to figure out how the server will communicate with each, etc. Researched
how to share variables and datatypes between clients (will probably have to used
shared memory and semaphores?). Theory: Shared memory on the computer running
the server so all processes can get "global variables."

(2 hours)

### 2026-01-08 - Contiuing tournament work, communication between forks.

Starting work with semaphores and shared memory to know when all clients are
connected. Looking back at old labs and just trying to remember how shared memory works
again. Have basic code structure down, but tomorrow I'll have to debug heavily.

(1 hour)

### 2026-01-09 - Finished (really debugged) game clients wait until player limit.

Debugged everything and game waiting feature works! All the subservers now all communicate properly
with each other until the desired player count (8) is reached via usage of semaphores and
shared memory. I used recv()'s blocking functionality to streamline waiting and plan
to use it in the future for sending game states. Continued to communicate with Louis on
readying and the actual game & merged.

(1.5 hours)
