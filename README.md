<h1>Kart Racer</h1>
<h2>What is Kart Racer?</h2>
Kart Racer was the game I made for my Final Year Project at Teesside University.

My goal was to create an online multiplayer game with a system to simulate a reduction in latency.

<h2>What Did I Make?</h2>
I created a Kart Racing game using the standard pawn in Unreal Engine which doesn't have smooth replicated movement.

I developed a client side prediction and server reconciliation system that would keep the server authoratative, meaning that the server is in charge of everything that happens, but also keeps the gameplay smooth for all clients and not needing to wait for a response from the server before moving.
All the simulated proxies in the game will be simulated based on the last move data recieved.

Moves are used to keep track of what is happening in the game. Moves are sent to the server which are then acknowledged when the move is deemed to be valid. If a move is not valid then a corrected version is sent to the clients and all moves from that point are replayed to correct the error.
