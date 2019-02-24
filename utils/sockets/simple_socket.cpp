#include <simple_socket.hpp>

// Read n_bytes from the socket into the location pointed to by `data`
ssize_t SimpleSocket::read(void* data, size_t n_bytes) {
    // If the socket is not open, return with no data
    if (!is_open())
        return 0;

    // Make sure that the errno variable is reset and does not contain old data.
    errno = -1;

    // Read from the file descriptor
    // Return value from read; contains either number of bytes read, or error.
    return close_if_error(::read(fd, data, n_bytes));
}

// Write n_bytes into the socket from the location pointed to by `data`
ssize_t SimpleSocket::write(void* data, size_t n_bytes) {
    // If the socket is not open, return with no data
    if (!is_open())
        return 0;

    // Make sure that the errno variable is reset and does not contain old data.
    errno = -1;

    // Read from the file descriptor
    // Return value from read; contains either number of bytes read, or error.
    return close_if_error(::write(fd, data, n_bytes));
}

// Decide what to do, given a socket return value
ssize_t SimpleSocket::close_if_error(ssize_t socket_return_value) {
    // 'End of file'. Peer hungup, close safely.
    if (socket_return_value == 0)
        close();

    // If there's a socket error, handle it
    if (socket_return_value < 0) {
        // If errno = EWOULDBLOCK, the socket is fine, it just hasn't received
        // anything yet. Otherwise, close the socket down.
        switch (errno) {
            case EWOULDBLOCK:  // Not an error, just nothing happened.
                break;
            case ECONNREFUSED:  // Connection was refused
            case ECONNRESET:    // Connection was reset
                close();
                break;
            default:  // Unhandled, real error.
                close();
                throw std::runtime_error(strerror(errno));
                break;
        }

        // Can be used like a boolean value, to indicate failure.
        return 0;
    } else {
        // Everything's fine, return the number of bytes that were manipulated.
        return socket_return_value;
    }
}

// Close the socket, and set it's file descriptor variable to -1 to indicate
// that it has closed.
void SimpleSocket::close() {
    if (is_open()) {
        ::close(fd);
        fd = -1;
    }
}

// Check to see whether the socket is still open
bool SimpleSocket::is_open() {
    return fd >= 0;
}

// Close the socket on deconstruction/out of scope
SimpleSocket::~SimpleSocket() {
    close();
}

// Tell a file socket that it should not block. Useful in derived classes.
bool set_socket_nonblock(int fd) {
    // Copy our current flags
    int flags = fcntl(fd, F_GETFL);
    if (flags < 0)
        return false;

    // Set new flags to include O_NONBLOCK
    int ret = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    if (ret < 0)
        return false;

    return true;
}
