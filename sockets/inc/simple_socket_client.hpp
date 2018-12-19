#pragma once

#include <iostream>
#include <simple_socket.hpp>

class SimpleSocketClient : public SimpleSocket {
	private:
		struct hostent *server_host;
	public:
		SimpleSocketClient (int port, char* ip);
		~SimpleSocketClient();
};
