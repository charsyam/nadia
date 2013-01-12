#pragma once

#include    "stream.h"

namespace nadia {

enum event_type{
    READ_EVENT = 01,
    WRITE_EVENT = 02,
    TIMEOUT_EVENT = 04,
    SIGNAL_EVENT = 010,
    CLOSE_EVENT = 020
};

class handler {
public:
    virtual ~handler(){}
    virtual int handle_close() = 0;
    virtual int handle_read() = 0;
    virtual int handle_write() = 0;
    virtual int handle_error() = 0;
    virtual int handle_timeout() = 0;
    virtual int handle_signal(int _sig) = 0;
    virtual handle get_handle() = 0 ;
};

}
