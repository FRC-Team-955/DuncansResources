#pragma once

#include <iostream>
#include <simple_socket.hpp>

class SimpleSocketServer : public SimpleSocket {
	private:
		int server_fd; // Server file descriptor, not to be confused with the client's
		socklen_t clilen; // Client address struct length
		struct sockaddr_in cli_addr; //Client address struct
	public:
		SimpleSocketServer (int port);
        bool keep_alive();
		~SimpleSocketServer();
};
