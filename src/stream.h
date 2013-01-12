#pragma once

#include    <unistd.h>
#include    <sys/uio.h>
#include    <netinet/in.h>
#include    <sys/socket.h>
#include    <netdb.h>
#include    <arpa/inet.h>

namespace nadia {

typedef     int     handle;
#define     INVALID_HANDLE      (-1)

class InetAddress {
public:
    InetAddress(const char* _port, bool _tcp, bool _ipv6 );
    ~InetAddress();

    struct addrinfo *get();

private:
    struct addrinfo *result_;
    struct addrinfo hint_;
};

class stream {
public:
    stream();
    stream(handle _handle);
    ~stream();

    void close();
    bool create(InetAddress& _inet,
                bool _nonblcok = false);

    handle get_handle();
    void set_closehandle(bool _close);
    bool get_closehandle();

    int read(char *buffer, int _size);
    int write(const char *buffer, int _size);

    int listen(int backlog = 10);

private:
    handle  handle_;
    bool    close_handle_;
};

}
