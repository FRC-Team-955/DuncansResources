#include <simple_socket_client.hpp>

SimpleSocketClient::SimpleSocketClient(std::string ip, int port) {
    this->port = port;
    this->ip = ip;
    this->server_host = nullptr;
    keep_alive();
}

bool SimpleSocketClient::keep_alive() {
    if (is_open()) return true;

    if (tmp_fd < 0) {
        server_host = nullptr;
        tmp_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (tmp_fd < 0) throw std::runtime_error("Socket creation failed");
        if (!set_socket_nonblock(tmp_fd)) throw std::runtime_error("Could not set socket to non-blocking");
    }

    if (!server_host) {
        server_host = gethostbyname(ip.c_str());

        // Clear server_host address struct
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;

        bcopy((char *)server_host->h_addr, (char *)&serv_addr.sin_addr.s_addr,server_host->h_length);

        serv_addr.sin_port = htons(port);
    }

    if (tmp_fd >= 0 && !!server_host) {
        if (connect(tmp_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
            switch (errno) {
                case EWOULDBLOCK:
                case EINPROGRESS:
                case ECONNREFUSED:
                    break;
                default:
                    throw std::runtime_error(strerror(errno));
                    break;
            }
            return false;
        } else {
            fd = tmp_fd;
            tmp_fd = -1;
            return true;
        }
    }
    return false;
}

SimpleSocketClient::~SimpleSocketClient() {}
