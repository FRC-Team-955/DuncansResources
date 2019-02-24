#include <stdio.h>
#include <stdlib.h>
#include <simple_socket_client.hpp>
#include <simple_socket_server.hpp>

// The size of the message buffer to use for incomming messages.
const size_t message_buffer_size = 512;

int main(int argc, char** argv) {
    // Base class pointer. Can be either represent a client, or a server.
    SimpleSocket* sock;

    // If there are any command line options, become a client
    if (argc > 1) {
        // Create a new client socket at ip 'localhost' on port 5060
        sock = new SimpleSocketClient("localhost", 5060);

        // If the socket is alive, write "hello" into it. If the server
        // is started first, they will echo this back to one another forever.
        while (sock->write((void*)"hello", 6) == 0) {
            usleep(1000 * 10);
            sock->re_establish();
        }
    } else {
        // Create a new socket server on port 5060
        sock = new SimpleSocketServer(5060);
    }

    // Buffer for incomming messages, instantiated with zeroes by using `= {0};`
    char buffer[message_buffer_size] = {0};

    while (true) {
        // Attempt to read up to <message_buffer_size> bytes into the message buffer
        ssize_t ret = sock->read(buffer, message_buffer_size);
        if (ret > 0) {
            // If there was anything received...

            // Print the message buffer contents
            printf("Message: %s\n", buffer);

            // Write the message buffer contents into the socket, reusing the length
            // of the read message as the length for the write message
            sock->write(buffer, ret);

            // Clear (zero) the buffer to await new messages
            bzero(buffer, 512);
        } else {
            // Nothing was received. Try to re-establish  Sleep so we don't spam the
            // kernel.
            sock->re_establish();
            usleep(1000 * 10);  // In microseconds, so this sleeps for 10 milliseconds.
        }
    }
}
