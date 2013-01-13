#pragma once

#include "handler.h"
#include "dispatcher.h"
#include "stream.h"

class EchoHandler : public nadia::handler {
public:
    EchoHandler(nadia::handle _handle, nadia::dispatcher *_dispatcher) : stream_(_handle), dispatcher_(_dispatcher), length_(0), reserved_(0) {
    };

    ~EchoHandler() {}

    int handle_close() {
        printf("Close: %d\n", stream_.get_handle());
        delete this;
        return 0;
    }

    int handle_read() {
        char buffer[4096];
        int n = stream_.read(buffer, 4095);
        if (n == 0) {
            return 0;
        }

        buffer[n] = 0;
        if (strcasecmp(buffer, "QUIT") == 0) {
            return 0;
        }

        printf("recv: %s\n", buffer);

        memcpy(outputbuffer_, buffer, n);
        length_ = reserved_ = n;
        dispatcher_->register_handler(this, (nadia::READWRITE_EVENT));

        return n;
    }

    int handle_write() {
        char *ptr = &outputbuffer_[length_ - reserved_];
        int n = stream_.write(ptr, reserved_);
        reserved_ -= n;
        if (reserved_ == 0) {
            dispatcher_->register_handler(this, nadia::READ_EVENT);
        }
        return n;
    }

    int handle_error() {
        return 0;
    }

    int handle_timeout() {
        return 0;
    }

    int handle_signal(int _sig) {
        return 0;
    }

    nadia::handle get_handle() {
        return stream_.get_handle();
    }

private:
    nadia::stream stream_;
    nadia::dispatcher *dispatcher_;
    char outputbuffer_[4096];
    int reserved_;
    int length_;
};
