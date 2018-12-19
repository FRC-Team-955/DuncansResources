#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <errno.h> 
#include <fcntl.h>

class SimpleSocket {
    public:
		int fd = -1; 
        int port;
		struct sockaddr_in serv_addr;
        ssize_t read(void* data, size_t n_bytes);
        ssize_t write(void* data, size_t n_bytes);
        bool is_open();
        void close();
        ~SimpleSocket();
    private:
        ssize_t close_if_error(ssize_t ret);
};

bool set_socket_nonblock(int fd);
