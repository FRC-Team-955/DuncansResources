#include <stdio.h>
#include <stdlib.h>
#include <simple_socket_client.hpp>
#include <simple_socket_server.hpp>

// The size of the message buffer to use for incomming messages.
const size_t message_buffer_size = 512;

int main (int argc, char** argv) {
    // Base class pointer. Can be either represent a client, or a server.
    SimpleSocket* sock;

    bool is_client = argc > 1;

    // If there are any command line options, become a client
    char message = '?';
    if (is_client) {

        // Create a new client socket at ip 'localhost' on port 5060
        sock = new SimpleSocketClient ("localhost", 5060);

        while (true) {
            printf("Enter a character (%i): ", sock->is_open());
            message = getchar();
            sock->read((void*)"", 0);
            sock->re_establish();
            if (sock->write(&message, 1)) {
                printf("Sucessfully wrote %c\n", message);
            } else {
                printf("Couldn't write (%s)\n", sock->is_open() ? "Connected" : "Disconnected");
                usleep(1000 * 100);
            }
        }
        
    } else {

        // Create a new socket server on port 5060
        sock = new SimpleSocketServer (5060);

        while (true) {
            sock->re_establish();
            if (sock->read(&message, 1)) {
                printf("Sucessfully read %c\n", message);
            } else {
                printf("Nothing to read (%s)\n", sock->is_open() ? "Connected" : "Disconnected");
                usleep(1000 * 100);
            }
        }
    }
}
