### SNOWCAST - A Radio

Clients communicate their UDP ports to the server via TCP/IP
Server broadcasts mp3 to the UDP port.
Clients can change the channel via TCP/IP . This is a shared memory .
As the channel changes the songs also get changed .

Usage:

1. Run Server:

  gcc server.c talker.c -lpthread -o server
  ./server

2. Run Client:

  gcc client.c -o client
  ./client
  [enter any number to go channel]

3. Run Listener

  gcc listener.c -o listener
  ./listener | mpg123 -

###TODO :  
Objective was to get the jist of the assignment even though I was not formally taking the course and
thus had other course load.

Things I skipped over.

1. TCP/IP communication , was extremely structured .

2. Broadcast to multiple clients through threads .

3. Multiple clients can communicate via both TCP/UDP

4. Different songs can be transmitted over different channels .
