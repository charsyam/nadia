#pragma once

namespace nadia {

template<typename EventLoop, typename Session>
class eventloop {
public:
    eventloop() : max_event_(0) {
        ep.create();
    }
    ~eventloop() {
        ep.close();
    }

    int event_add_session(Session *_session) {
        return ep.add_session(_session);
    }

    int event_add_out(Session *_session) {
        return ep.add_out(_session);
    }

    int event_del_out(Session *_session) {
        return ep.del_out(_session);
    }

    int poll(int _timeout) {
        int ret;
        for(;;) {
            ret = ep.poll( events, max_event_, _timeout );
            if( 0 == ret ) {
            }
        }

        return ret;
    }

private:
    typedef     EventLoop<Session>::event        event;
    EventLoop<Session>   ep;
    int         max_event_;
};
    
#if defined(__linux__)
typedef class eventloop<EpollEventLoop> eventprocess;
#else
#warning "Not Supported IO"
#endif

}
