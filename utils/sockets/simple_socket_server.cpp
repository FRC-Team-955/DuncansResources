#include <simple_socket_server.hpp>

// Construct a new SimpleSocketServer, open on `port`
SimpleSocketServer::SimpleSocketServer(int port) {
    // Set port
    this->port = port;

    // Create the server socket file descriptor. This is not to be confused with 
    // the client socket file descriptor that the base class contains.
    // This socket is used to indicated when a new client has connected, and
    // to accept() the new client.
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Throw an exception if the socket could not be created
    if (server_fd < 0) throw std::runtime_error("Could not open socket");

    // Clear the server addresss struct
    bzero((char *) &serv_addr, sizeof(serv_addr));
    // Use IP v4
    serv_addr.sin_family = AF_INET;
    // Any input address
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    // Set port
    serv_addr.sin_port = htons(port);

    //http://stackoverflow.com/questions/5592747/bind-error-while-recreating-socket
    // Allow the socket to overwrite a previous socket on the same port
    int yes=1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        throw std::runtime_error("Socket bind option error");
    }

    // Bind the address to the socket
    if (bind(server_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        throw std::runtime_error("Socket bind error");
    }

    // Begin listening on the socket
    listen(server_fd,5);

    // Set client struct length field. Useful on accept.
    this->clilen = sizeof(cli_addr);

    // Do not block when checking for a new client 
    set_socket_nonblock(server_fd);

    // Attempt to find and connect to a client immediately.
    re_establish();
}

// If the client has disconnected, check for a new connection. Otherwise, return
// true. Can be called faily often as it does not block, and makes no kernel
// calls when the socket is already open.
void SimpleSocketServer::re_establish() {
    // If we already have an open socket, do nothing.
    if (is_open()) return;

    // Attempt to handle a new client, and store the file descriptor 
    // in a temporary location.
    int tmp_fd = accept(server_fd, (struct sockaddr *) &cli_addr, &clilen);

    // Determine whether there has been an error
    if (tmp_fd < 0) { 
        if (errno != EWOULDBLOCK) {
            // There has been a real error, halt and report.
            throw std::runtime_error(strerror(errno));
            return;
        }

        // The server cannot accept a new client because there are none trying to connect. Move on.
        return;
    } else {
        // A new client has connected! Assign the fd field of the base class, and set the socket to non-blocking.
        this->fd = tmp_fd;
        if (!set_socket_nonblock(this->fd)) {
            throw std::runtime_error("Could not set socket to non-blocking");
        }

        // Green across the board. We now have a working socket. Hopefully.
        return;
    }
}

// Close the server fd when deconstructing. Note that the base class deconstructor
// is called automatically, so we do not (and should not) close it here.
SimpleSocketServer::~SimpleSocketServer() {
    ::close(server_fd);
}
