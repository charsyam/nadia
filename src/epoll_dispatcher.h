#pragma once

#include    "handler.h"
#include    <sys/epoll.h>
#include    <errno.h>
#include    <unistd.h>
#include    <map>

namespace nadia {

typedef     handle      TIMER_ID;
typedef     handle      SIGNAL_ID;

class epoll_dispatcher {
public:
    epoll_dispatcher();
    ~epoll_dispatcher();

    int register_handler(handler *_e, event_type _et);
    int unregister_handler(handler *_e, event_type _et);
    int handle_events();

private:
    int register_timer_handler(handler *_e);
    int unregister_timer_handler(handler *_e);

    int register_signal_handler(handler *_e);
    int unregister_signal_handler(handler *_e);

    int mask_ops(handler* _h, event_type _et, int _op);
    int handles(struct epoll_event &_event);

private:
    handle  ep_;
    std::map<TIMER_ID, handler*> timer_handlers_;
    std::map<SIGNAL_ID, handler*> signal_handlers_;
    struct epoll_event *events_;
    int max_events_;
};

}
