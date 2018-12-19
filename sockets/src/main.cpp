#include <iostream>
#include <simple_socket.hpp>
#include <simple_socket_client.hpp>
#include <simple_socket_server.hpp>

int main () {
    SimpleSocketServer sock(5060);
    char buffer[512];
    while (1) {
        bzero(buffer, 512);
        printf("alive: %i\n", sock.keep_alive());
        ssize_t ret = 0;
        if (ret = sock.read(buffer, 512)) {
            printf("Message: %s\n", buffer);
            sock.write(buffer, ret);
        } else {
            usleep(1000 * 10);
        }
    }
}
