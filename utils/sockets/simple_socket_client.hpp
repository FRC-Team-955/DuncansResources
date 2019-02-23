#pragma once

#include <simple_socket.hpp>

class SimpleSocketClient : public SimpleSocket {
	public:
        // Constructor
		SimpleSocketClient (std::string ip, int port);

        // Destructor
        ~SimpleSocketClient();

        // Temporary file descriptor. Used to hide an in-progress connection
        // from the base class. Isn't connected to anything yet. Invalid when -1.
        int tmp_fd = -1;

        // See simple_socket.*pp
        void re_establish();

	private:
        // Information about a remote host (server)
		struct hostent *server_host = nullptr;

        // Store the ip so we can reconnect later
        std::string ip;
};
