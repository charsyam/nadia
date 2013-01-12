#include    "epoll_dispatcher.h"

namespace nadia {

epoll_dispatcher::epoll_dispatcher() : max_events_(1024), ep_(INVALID_HANDLE) {
    ep_ = epoll_create(max_events_);
    events_ = new struct epoll_event[max_events_];
}

epoll_dispatcher::~epoll_dispatcher() {
    if (INVALID_HANDLE != ep_) {
        close(ep_);
        ep_ = INVALID_HANDLE;
    }
}

void set_event_type(struct epoll_event &_event, handler *_h, event_type _et) {
    int status = EPOLLET;
    if (_et & READ_EVENT) {
        status |= EPOLLIN;
    }
    if (_et & WRITE_EVENT) {
        status |= EPOLLOUT;
    }

    _event.events = status;
    _event.data.ptr = _h;
}

int epoll_dispatcher::mask_ops(handler* _h, event_type _et, int _op) {
    struct epoll_event event;
    int status;

    set_event_type(event, _h, _et);
    status = epoll_ctl(ep_, _op, _h->get_handle(), &event);
    if (status < 0) {
        if (EPOLL_CTL_MOD != _op || ENOENT != errno ||
            epoll_ctl(ep_, EPOLL_CTL_ADD, _h->get_handle(), &event) == -1) {  
            return -1;
        }
    }

    return 0;
}

int epoll_dispatcher::register_timer_handler(handler *_h) {
    timer_handlers_.insert(std::pair<TIMER_ID, handler*>(_h->get_handle(), _h));
    return 0;
}

int epoll_dispatcher::unregister_timer_handler(handler *_h) {
    timer_handlers_.erase(_h->get_handle());
    return 0;
}

int epoll_dispatcher::unregister_signal_handler(handler *_h) {
    signal_handlers_.erase(_h->get_handle());
    return 0;
}

int epoll_dispatcher::register_signal_handler(handler *_h) {
    signal_handlers_.insert(std::pair<SIGNAL_ID, handler*>(_h->get_handle(), _h));
    return 0;
}

int epoll_dispatcher::register_handler(handler *_h, event_type _et) {
    if (TIMEOUT_EVENT & _et) {
        return register_timer_handler(_h);
    }else if (SIGNAL_EVENT & _et) {
        return register_signal_handler(_h);
    }

    return mask_ops(_h, _et, EPOLL_CTL_MOD);
}

int epoll_dispatcher::unregister_handler(handler *_h, event_type _et) {
    if (TIMEOUT_EVENT & _et) {
        return unregister_timer_handler(_h);
    }else if (SIGNAL_EVENT & _et) {
        return unregister_signal_handler(_h);
    }

    return mask_ops(_h, _et, EPOLL_CTL_DEL);
}

int epoll_dispatcher::handles(struct epoll_event &_event) {
    handler *h = (handler *)_event.data.ptr;

    if ((EPOLLERR) & _event.events) {
        h->handle_error();
        return -1;
    }
    if ((EPOLLIN | EPOLLHUP) & _event.events) {
        if (h->handle_read() == 0) {
            h->handle_close();
            return -1;
        }
    }
    if ((EPOLLOUT) & _event.events) {
        if (h->handle_write() == 0) {
            h->handle_close();
            return -1;
        }
    }

    return 0;
}

int epoll_dispatcher::handle_events() {
    int timeout = 0;
    int n = epoll_wait(ep_, events_, max_events_, timeout);
    if (n > 0) {
        for (int i = 0; i < n; i++) {
            handles(events_[i]);
        }
    } else if (n == 0) {
        //timer or signal
        return 0;
    }

    if (errno == EINTR) {
    }

    return -1;
}

}
