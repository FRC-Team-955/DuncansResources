#include <simple_socket.hpp>

// Read n_bytes from the socket into the location pointed to by `data`
ssize_t SimpleSocket::read(void* data, size_t n_bytes) {
    // Make sure that the errno variable is reset and does not contain old data.
    errno = -1;

    // Read from the file descriptor
    // Return value from read; contains either number of bytes read, or error.
    return close_if_error(::read(fd, data, n_bytes));

}

// Write n_bytes into the socket from the location pointed to by `data`
ssize_t SimpleSocket::write(void* data, size_t n_bytes) {
    // Make sure that the errno variable is reset and does not contain old data.
    errno = -1;

    // Read from the file descriptor
    // Return value from read; contains either number of bytes read, or error.
    return close_if_error(::write(fd, data, n_bytes));

}

// Decide what to do, given a socket return value
ssize_t SimpleSocket::close_if_error(ssize_t ret) {
    // Check status of file desciptor
    if (ret <= 0) {

        // If read() or write() return 0 or -1, check to make sure that the socket has not closed
        if (errno == EWOULDBLOCK) {
            // The socket is fine, it just hasn't received anything yet.
            return 0;
        } else {

            // The socket has experienced an error, close it safely.
            close();
            return 0;
        }
    }

    // Return the number of bytes that were manipulated.
    return ret;
}

// Close the socket, and set it's file descriptor variable to -1 to indicate that it has closed.
void SimpleSocket::close() {
    ::close(fd);
    fd = -1;
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
    if (flags < 0) return false;

    // Set new flags to include O_NONBLOCK
    int ret = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    if (ret < 0) return false;

    return true;
}
