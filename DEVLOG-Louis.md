# Dev Log:

This document must be updated daily every time you finish a work session.

## Louis Oh-Aronson

### 2026-01-06 - Setting up
Update proposal to include semaphores and switch timing on some goals, started working on semaphore implementation so that the client can "ready up" to start the tournament, after I did all this I realized semaphores across IP addresses is ridiculously complicated and I can just send a fixed-size message as they pair. I set up the ready-up sending on the client's side, and I'll do the ready-up receiving on the server's side tomorrow.

### 2026-01-07 - Receiving ready signals on the server's end pt 1
Created an 8 integer array in shared memory so that the parent server knows when all players are ready, created a simple loop for the parent to wait for the players to all be ready before anything can continue. Will figure out the child side of it tomorrow, plus a waiting screen for the user (possibly telling them which players haven't readied up). Will also work out the semaphore stuff that I need to use for the parent-child server shm.

### 2026-01-08 - Receiving ready signals on the server's end pt 2
Created semaphore to make sure there isn't reading and writing happening at the same time between the different children and parents. I'll make child receiving of readiness and waiting screen tmrw

### 2026-01-11 (and 01-12) - Making the tic tac toe game
Connect four was too hard, had to pivot. Will instead implement tic tac toe through the use of shared memory on the server side with a simple array of ints (0 for empty, 1 for x, 2 for o). If the game ends in a stalemate, it will go to whoever didn't have first move.

### 2026-01-12 (at night) - Implementing tic tac toe
Started by creating the move logic and win/loss handling for the client, then moved on to the server side where I implemented writing the boards in shared memory, then used h files to clean a bunch of stuff up, then developed win-checking conditions. Still need to figure out bracket play after the first game.

### 2026-01-13 (in class and at home) - debugging and head scratching
Worked on fixing char to int conversions, there is more to be done on the server side as well to make sure everything works.

### 2026-01-14 (in class) - still debugging blocking issues
Worked on issues with the amount of bytes and blocking using select as well as diagnosing many problems

### 2026-01-15 - Finishing touches
