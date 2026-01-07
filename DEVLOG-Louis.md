# Dev Log:

This document must be updated daily every time you finish a work session.

## Louis Oh-Aronson

### 2024-01-06 - Setting up
Update proposal to include semaphores and switch timing on some goals, started working on semaphore implementation so that the client can "ready up" to start the tournament, after I did all this I realized semaphores across IP addresses is ridiculously complicated and I can just send a fixed-size message as they pair. I set up the ready-up sending on the client's side, and I'll do the ready-up receiving on the server's side tomorrow.
