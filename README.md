[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/QfAIDTGi)

# Tournament Connect 4

### OH!... —WHEN?

Owen Shi & Louis Oh-Aronson

### Project Description:

This is a Tic Tac Toe tournament with 8 players. The players will be separated into tournament brackets and compete against one another in rounds for a final
winner!

### Instructions:

Server Commands:

- make server-run
  - Automatically compiles and runs the server
- make server-compile
  - Compiles the server

Client Commands:

- make client-run (with optional argument of an IP address)
  - Automatically compiles and runs the client
  - If an IP address and port of a running server are passed, it will connect to that server.
- make client-compile
  Compiles the client

How does the user interact with this program?
Well, there are a few ways!

First, if you are weird (or testing functionality) and want to play a bunch of tic tac toe games against yourself, we recommend that you use tmux so that you can run the 8 clients necessary, since all 8 clients must be connected for games to start. Tmux usage allows you to not open 9 windows on your machine, but may limit scrolling potential.

Second, if you are more normal and want to play with friends, you can have one person set up the server and share its IP address and port (provided the port is set up to allow outside connections), then all 8 friends can connect (hopefully you don't have more because that feature hasn't been released yet)! From then on, you just play 1-3 normal games of tic tac toe (depending, of course, upon if you win or lose), until a champion is crowned at the end! Don't tell anyone, but if you pay us $50 (literally enter "$50" as a move), player 1 will instantly win! Perhaps just maybe don't enter the cheat code when you're player 2 (the lower seed).

Last but not least, no matter what if you kill the client process at any time during a game and the socket closes, it counts as an immediate forfeit!!

### Resources/ References:
Systems website (konstantinnovation.github.io), W3Schools and GeeksforGeeks to help debug some small errors with understanding the parameters of functions.
