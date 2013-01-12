#pragma once

#include    "handler.h"

namespace nadia {

template<typename POLL>
class dispatcher {
public:
    ~dispatcher() {}

    int register_handler(handler *_h, event_type _event) {
        return poll_.register_handler(_h, _event);
    }

    int unregister_handler(handler *_h, event_type _event) {
        return poll_.unregister_handler(_h, _event);
    }

    int handle_events() {
        return poll_.handle_events();
    }

private:
    POLL poll_;
};

}
