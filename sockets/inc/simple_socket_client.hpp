#pragma once

#include <iostream>
#include <simple_socket.hpp>

class SimpleSocketClient : public SimpleSocket {
	private:
		struct hostent *server_host = nullptr;
        std::string ip;
	public:
		SimpleSocketClient (std::string ip, int port);
        int tmp_fd = -1;
        void reset();
        bool keep_alive();
        ~SimpleSocketClient();
};
