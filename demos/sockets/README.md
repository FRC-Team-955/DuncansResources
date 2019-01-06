# Sockets

## Try the example

This project contains a set of classes for interacting with asynchronous sockets in a simple way. To try this example, compile the source according to the guidelines in the README.md located at the repository's root.

You'll probably want to open another terminal to try this out. In the first, run:
```
./build/socket_example
```

This will start a socket server on your machine. Switch to the other terminal, and run:
```
./build/socket_example --client
```
(Note that it doesn't need to be '--client' - I got lazy and didn't do the command line parsing. It just checks if there are any arguments).

This will run the client program. The client will connect to the server, and write 'hello' into the socket. In the other terminal, the server should print 'hello'. Soon there will be thousands of 'hello' entries, because the message will bounce back and forth between the client and server until you hit \<Ctrl-C\> on one of them. 

## Using the socket API
Because this library is so small and custom, I did not bother turning it into a binary and set of headers. It's best to just copy the simple\_socket\*.\*pp files into your project's source. 

See `src/main.cpp` for a simple example of using the sockets. Note how I use the base class `SimpleSocket` to represent the socket after I create it with either `SimpleSocketClient` or `SimpleSocketServer`. I recommend you do the same, in case you want to transpose which device is the socket client/server later. Keep in mind that it does not have to be allocated on the heap (`new SimpleSocket*`) like it is here, I just do that so that the type of socket is determined at runtime; this is unusual and is only for demonstration/laziness purposes.

## Limitations
The library is intended only to be used for asynchronous sockets. This means that in order to use the library, you have to call `sock.keep_alive()` frequently to maintain contact. You will have to build the flow of your program around this limitation. This is a marginal improvement upon the default alternative - blocking sockets - which halt your program while the socket is waiting to send or receive a message. 

Furthermore, the socket server class only allows one client to connect at any given time. To handle more than one client, you would need to create more server socket classes with unique ports. This is not even close to ideal. If you want to try to handle multiple clients, look into `poll(2)`, `epoll(7)`, or `select(3)`. My favorite is `poll(2)` for it's simplicity and ease of use. Take a look at 'more guides'. 

If the socket is still closed and you try to `write()` or `read()` it, it may throw an exception. Try to make sure the socket is alive (`.keep_alive()`) before a communication burst.

## More guides
If you'd like to know more about sockets in general, I'd recommend Beej's networking guide:

http://beej.us/guide/bgnet/html/single/bgnet.html

While not providing clear tutorials, the manual pages describing Linux API calls are invaluable. For example, to learn about the `socket(7)` call, run:
```
man 7 socket
```
or to learn about `poll(2)` you can run:
```
man 2 poll
```
