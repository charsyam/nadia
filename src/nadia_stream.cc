#include    "nadia_stream.h"
#include    <string.h>
#include    <stdio.h>

namespace nadia {

InetAddress::InetAddress(const char *_port, bool _tcp, bool _ipv6) 
                        : result_(NULL) {
    memset(&hint_, 0, sizeof(struct addrinfo));

    hint_.ai_flags = AI_PASSIVE;
    hint_.ai_family = AF_INET;
    if (_ipv6) {
        hint_.ai_family = AF_INET6;
    }

    hint_.ai_socktype = SOCK_DGRAM;
    if (_tcp) {
        hint_.ai_family = SOCK_STREAM;
    }

    if (getaddrinfo(NULL, _port, &hint_, &result_) != 0) {
        result_ = NULL;
    }
}

InetAddress::~InetAddress() {
    if (result_) {
        freeaddrinfo(result_);        
        result_ = NULL;
    }
}

struct addrinfo *InetAddress::get() {
    return result_;
}

stream::stream() : handle_(INVALID_HANDLE), close_handle_(true) {
}

stream::stream(handle _handle) : handle_(_handle), close_handle_(true) {
}

stream::~stream() {
    if (close_handle_) {
        close();
    }
}

bool stream::create(InetAddress& _inet, bool _nonblock) {
    struct addrinfo *info = _inet.get();
    if (NULL == info) {
        return false;
    }

    int stream = info->ai_socktype | _nonblock;

    handle_ = ::socket(info->ai_family,
                       stream,
                       info->ai_protocol);

    return (INVALID_HANDLE != handle_);
}

void stream::close() {
    if (INVALID_HANDLE != handle_) {
        ::close(handle_);
        handle_ = INVALID_HANDLE;
    }
}

void stream::set_closehandle(bool _close) {
    this->close_handle_ = _close;
}

bool stream::get_closehandle() {
    return close_handle_;
}

handle stream::get_handle() {
    return handle_;
}


}
