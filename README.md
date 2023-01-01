# TCP project

This project consists of four executables: `Measure`, `sender`, `client`, and `server`.

## Requirements

- gcc compiler
- make (optional)

## Building the executables

To build all four executables, run:

```bash
make all
```

## Running the executables
To run the Measure executable, run:   
`make runs`
To run the sender executable, run:  
`make runc`

## What the executables do
Measure
The Measure executable measures the time taken to send a file over a network.

sender
The sender executable sends a file to a server.

client
The client executable connects to a server at IP address 10.0.2.15 and port 5000. It then opens a file called "1gb.txt" and reads the contents of the file in chunks of size 100 bytes and sends them to the server. It also measures the time taken to send the file and prints it.

The client executable also gets and sets the TCP congestion control algorithm for the socket connection. It first gets the current congestion control algorithm, then sets it to "reno", and then gets it again to confirm that the change was made.

server
The server executable creates a server socket and binds it to IP address INADDR_ANY (all available interfaces) and port 5000. It listens for incoming connections and accepts them when they occur.

For each accepted connection, it receives data in chunks of 1024 bytes and writes it to a file called "provacopy.txt" until all the data has been received. It also measures the time taken to receive the file and prints it.

Finally, it closes the accepted connection and continues listening for new connections.
