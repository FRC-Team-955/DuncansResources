#pragma once

#include <stdexcept>
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
    // Allow derived classes to access private members
    friend class SimpleSocketServer;
    friend class SimpleSocketClient;

    public:
		int fd = -1; 
        int port;
		struct sockaddr_in serv_addr;
        ssize_t read(void* data, size_t n_bytes);
        ssize_t write(void* data, size_t n_bytes);
        virtual bool keep_alive() = 0;
        ~SimpleSocket();
    private:
        bool is_open();
        void close();
        ssize_t close_if_error(ssize_t ret);
};

bool set_socket_nonblock(int fd);
