[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/QfAIDTGi)

# 8-Player Tournament Tic-Tac-Toe

### OH!... —WHEN?

Owen Shi & Louis Oh-Aronson

### Project Description:

This is a Tic Tac Toe tournament with 8 players. The players will be separated 3 different rounds of brackets (qualifiers, semifinals, and finals) and compete in a very intense game of Tic-Tac-Toe to determine a grand winner. The prize is bragging rights!

At it's core, a forking server and shared memory addresses are used as a proxy to facilitate client-client communication. We have a game state struct that is constantly being sent back and forth, and manipulated when each bracket ends to determine the next set of matchups.

### Instructions:

#### Server Setup & Comnmands:

Generally, to start the server, simply run a `make server-run` and the server will automatically compile and run. It will listen for clients until 8 are connected, and then start the tournament.

If you wish to only compile the server, then just run a `make server-compile`.

#### Client Setup & Commands:

Like the server, to start the client, simply run a `make client-run` and the client will automatically compile and run. The client will be blocked from doing anything until the server has 8 clients connected.

To only compile the client (without running), do `make client-compile`

For clients and servers on different IP addresses, you'll have to compile the client and then run `./client {IP_ADDRESS}`.

#### How does the user interact with this program?

Well, there are a few ways!

First, if you are weird (or testing functionality) and want to play a bunch of tic tac toe games against yourself, we recommend that you use tmux so that you can run the 8 clients necessary, since all 8 clients must be connected for games to start. Tmux usage allows you to not open 9 windows on your machine, but may limit scrolling potential.

Second, if you are more normal and want to play with friends, you can have one person set up the server and share its IP address and port (provided the port is set up to allow outside connections), then all 8 friends can connect (hopefully you don't have more because that feature hasn't been released yet)! From then on, you just play 1-3 normal games of tic tac toe (depending, of course, upon if you win or lose), until a champion is crowned at the end! Don't tell anyone, but if you pay us $50 (literally enter "$50" as a move), player 1 will instantly win! Perhaps just maybe don't enter the cheat code when you're player 2 (the lower seed).

### Resources/ References:

https://beej.us/guide/bgnet/html/
https://konstantinnovation.github.io/systems.html
