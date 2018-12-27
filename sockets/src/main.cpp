#include <stdio.h>
#include <stdlib.h>
#include <simple_socket_client.hpp>
#include <simple_socket_server.hpp>

// The size of the message buffer to use for incomming messages.
const size_t message_buffer_size = 512;

int main (int argc, char** argv) {
    // Base class pointer. Can be either represent a client, or a server.
    SimpleSocket* sock;

    // If there are any command line options, become a client
    if (argc > 1) {

        // Create a new client socket at ip 'localhost' on port 5060
        sock = new SimpleSocketClient ("localhost", 5060);

        // If the socket is alive, write "hello" into it. If the server 
        // is started first, they will echo this back to one another forever.
        if (sock->keep_alive()) sock->write((void*)"hello", 6);
    } else {

        // Create a new socket server on port 5060
        sock = new SimpleSocketServer (5060);
    }

    // Buffer for incomming messages, instantiated with zeroes by using `= {0};`
    char buffer[message_buffer_size] = {0};

    while (1) {
        // Attempt to keep the socket alive, and check status while doing so.
        bool alive = sock->keep_alive();

        // Return value from the socket. Will be equal to the 
        // number of bytes read or written if not zero.
        ssize_t ret = 0;

        // Check if the socket is alive, and if so, read up to 512 bytes into the message buffer
        if (alive && (ret = sock->read(buffer, message_buffer_size))) {
            // If there was anything received...

            // Print the message buffer contents
            printf("Message: %s\n", buffer);

            // Write the message buffer contents into the socket, reusing the length of the 
            // read message as the length for the write message
            sock->write(buffer, ret);

            // Clear (zero) the buffer to await new messages
            bzero(buffer, 512);
        } else {
            // Nothing was received. Sleep so we don't spam the kernel.
            usleep(1000 * 10); // In microseconds, so this sleeps for 10 milliseconds.
        }
    }
}
