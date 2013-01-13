#pragma once

#include "handler.h"
#include "stream.h"
#include "dispatcher.h"

namespace nadia {

template<typename HANDLER>
class acceptor : public handler {
public:
    acceptor(handle _handle, dispatcher *_dispatcher) : dispatcher_(_dispatcher), stream_(_handle) {
        int yes = 1;
        if (setsockopt(stream_.get_handle(), SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            
        }
    }
    ~acceptor(){}
    int handle_close() {
        return 0;
    }

    int handle_read() {
        handle new_handle = ::accept(stream_.get_handle(), NULL, NULL);
        if (new_handle > 0) {
            dispatcher_->register_handler(new HANDLER(new_handle, dispatcher_), READ_EVENT);
        }

        return new_handle;
    }

    int handle_write() {
        return 0;
    }

    int handle_error() {
        return 0;
    }

    int handle_timeout() {
        return -1;
    }

    int handle_signal(int _sig) {
        return -1;
    }

    handle get_handle() {
        stream_.get_handle();
    }

private:
    stream  stream_;
    dispatcher *dispatcher_;    
};

}
