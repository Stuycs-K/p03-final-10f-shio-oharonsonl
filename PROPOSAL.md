# Final Project Proposal

## Group Members:

Owen Shi & Louis Oh-Aronson

# Intentions:

We are trying to make a tournament-style connect four game. It will be for 8 players and have 3 brackets: qualifiers, semi-finals, and finals.

# Intended usage:

Run the server on one computer that will also play the game. Other players will connect to that server's IP via terminal commands. While this happens,
the server will automatically display the current number of players while waiting for the correct number of players, automatically creating
games and sending the messages back to the clients to display. It'll go back and forth from input to a waiting period to a resulting output and another input.

# Technical Details:

We’ll use sockets to connect 8 players, then use process control (fork/wait) to run matches while the main server keeps the bracket moving. We’ll use
dynamic memory and semaphores to store player info, boards, and bracket state, and use signals (like SIGCHLD) to clean up finished match processes and handle disconnects cleanly.

# Intended pacing:

Initial forking setup (Jan. 7th) - Owen

Semaphore setup so that players can "ready up" (Jan 7th) - Louis

Bracket logic & game assignments (Jan. 12th) - Owen

Player waiting screen (Jan 9th) - Louis

Game functionality (Jan 12th) - Louis

Merge game with tournament server (Jan 12th) - Louis

Player resign, draw request through signals? (Jan 15th)  - Owen and Louis

Bug fixes (Jan 15th) - Owen and Louis

Smoothen everything, make it look nice (Jan 15th) - Owen and Louis
