#include <iostream>
#include <simple_socket.hpp>
#include <simple_socket_client.hpp>
#include <simple_socket_server.hpp>

int main (int argc, char** argv) {
    SimpleSocket* sock;
    if (argc > 1) {
        sock = new SimpleSocketClient ("localhost", 5060);
        if (sock->keep_alive()) sock->write((void*)"what", 5);
    } else {
        sock = new SimpleSocketServer (5060);
    }

    char buffer[512] = {0};
    while (1) {
        bool alive = sock->keep_alive();
        printf("alive: %i\n", alive);
        ssize_t ret = 0;
        if (alive && (ret = sock->read(buffer, 512))) {
            printf("Message: %s\n", buffer);
            sock->write(buffer, ret);
            bzero(buffer, 512);
        } else {
            usleep(1000 * 10);
        }
    }
}
