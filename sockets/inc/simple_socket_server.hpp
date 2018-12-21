#pragma once

#include <simple_socket.hpp>

class SimpleSocketServer : public SimpleSocket {
	public:
        // Constructor
		SimpleSocketServer (int port);
        
        // Destructor
		~SimpleSocketServer();

        // See simple_socket.*pp
        bool keep_alive();
	private:
        // Server file descriptor, not to be confused with the client's.
        // See socket(..) in simple_socket_server.cpp
		int server_fd; 

        // Client address struct length, relevent in accept(...)
		socklen_t clilen; 

        //Client address struct
		struct sockaddr_in cli_addr; 
};
