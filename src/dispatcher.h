#pragma once

#include    "handler.h"

namespace nadia {

class dispatcher {
public:
    ~dispatcher() {}
    virtual int register_handler(handler *_h, event_type _event) = 0;
    virtual int unregister_handler(handler *_h, event_type _event) = 0;
    virtual int handle_events() = 0;
};

}
