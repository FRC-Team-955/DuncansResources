#pragma once

#include <stdexcept> // Sane-ish exceptions
#include <stdio.h> // Standard libs for socket io, etc. 
#include <stdlib.h> // Ditto
#include <unistd.h> // close(), etc.
#include <string.h> // bzero, etc.
#include <sys/types.h> // ssize_t, etc.
#include <sys/socket.h> // sockets
#include <netinet/in.h> // address families
#include <netdb.h> // gethostbyname, etc.
#include <errno.h> // C api error handling
#include <fcntl.h> // Flags/non-blocking

// A simple socket, base class for client and server objects to inherit from. 
// Represents a socket that can be written to and read from.
class SimpleSocket {
    // Allow derived classes to access private members
    friend class SimpleSocketServer;
    friend class SimpleSocketClient;

    public:
		int fd = -1; 
        int port;
		struct sockaddr_in serv_addr;

        // Read from the socket into `data` for n_bytes length. Returns 0 if there are no bytes available.
        ssize_t read(void* data, size_t n_bytes);

        // Write `data` to the socket for n_bytes length. Returns 0 if there were no bytes written.
        ssize_t write(void* data, size_t n_bytes);

        // Keep the derived class alive. In order to maintain an open connection, 
        // this should be called regularly. Returns whether the socket is actually
        // alive or not, after attempting to reconnect if there has been an error/disconnection.
        virtual bool keep_alive() = 0;

        // Base clase destructor. Called when derived classes are destructed.
        ~SimpleSocket();

    private:
        // Internal function to determine if the socket is currently open
        bool is_open();

        // Internal function to forcibly close the socket
        void close();

        // Check whether the return value and `errno` produced by a socket 
        // indicates an error, or return the number of bytes manipulated.
        ssize_t close_if_error(ssize_t ret);
};

// Convenience function for derived classes to set a socket to non-blocking.
bool set_socket_nonblock(int fd);
