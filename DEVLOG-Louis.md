# Dev Log:

This document must be updated daily every time you finish a work session.

## Louis Oh-Aronson

### 2026-01-06 - Setting up
Update proposal to include semaphores and switch timing on some goals, started working on semaphore implementation so that the client can "ready up" to start the tournament, after I did all this I realized semaphores across IP addresses is ridiculously complicated and I can just send a fixed-size message as they pair. I set up the ready-up sending on the client's side, and I'll do the ready-up receiving on the server's side tomorrow.

### 2026-01-07 - Receiving ready signals on the server's end
Created an 8 integer array in shared memory so that the parent server knows when all players are ready, created a simple loop for the parent to wait for the players to all be ready before anything can continue. Will figure out the child side of it tomorrow, plus a waiting screen for the user (possibly telling them which players haven't readied up). Will also work out the semaphore stuff that I need to use for the parent-child server shm.
