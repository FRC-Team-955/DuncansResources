#include <simple_socket_client.hpp>

// Construct a new simple socket client at ip and port.
SimpleSocketClient::SimpleSocketClient(std::string ip, int port) {
    // Assign internals
    this->port = port;
    this->ip = ip;

    // Ignore SIGPIPE from write fail
    signal(SIGPIPE, SIG_IGN);

    // Try to connect immediately
    re_establish();
}

void SimpleSocketClient::re_establish() {
    // If it ain't broke, don't fix it
    if (is_open()) return;

    // We haven't assigned the temporary file descriptor either
    if (tmp_fd < 0) {
        
        // Assume the host address isn't valid either
        server_host = nullptr;

        // Create a new temporary file descriptor
        tmp_fd = socket(AF_INET, SOCK_STREAM, 0);

        // Check error
        if (tmp_fd < 0) throw std::runtime_error("Socket creation failed");

        // Set it to non-blocking
        if (!set_socket_nonblock(tmp_fd)) 
            throw std::runtime_error("Could not set socket to non-blocking");
    }

    // We don't know if the host even exists. Try to find it.
    if (!server_host) {

        // Find the host
        server_host = gethostbyname(ip.c_str());

        // Clear server_host address struct
        bzero((char *) &serv_addr, sizeof(serv_addr));

        // Use IPv4
        serv_addr.sin_family = AF_INET;

        // Set host attributes
        bcopy((char *)server_host->h_addr, (char *)&serv_addr.sin_addr.s_addr,server_host->h_length);

        // Set port
        serv_addr.sin_port = htons(port);
    }

    // We know who the server is, and we have a temporary fd waiting. Attempt to connect
    if (tmp_fd >= 0 && !!server_host) {
        if (connect(tmp_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
            // Connection failed. Why?
            switch (errno) {
                case EWOULDBLOCK: // Still nothing to connect to on the host
                case ECONNREFUSED: // Ditto
                case EINPROGRESS: // Ditto
                case EALREADY: // Ditto
                    break; // Ignore it and move on
                default:
                    // This is a real error, halt and report it.
                    throw std::runtime_error(strerror(errno));
                    break;
            }

            // We're still not connected.
            return;
        } else {
            // Assign the real file descriptor, which opens the connection for use!
            this->fd = tmp_fd;

            // Invalidate the temporary fd, we don't need it anymore.
            tmp_fd = -1;
            return;
        }
    }
}

SimpleSocketClient::~SimpleSocketClient() {
    // If we're deconstructed while the temp fd is active, remove it.
    if (tmp_fd >= 0) ::close(tmp_fd);
}
