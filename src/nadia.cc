#include    <stdio.h>
#include    "stream.h"
#include    "handler.h"
#include    "dispatcher.h"
#include    "epoll_dispatcher.h"
#include    "acceptor.h"

class EchoHandler : public nadia::handler {
public:
    EchoHandler(nadia::handle _handle) : stream_(_handle) {
    };

    int handle_close() {
        return 0;
    }

    int handle_read() {
        char buffer[4096];
        int n = stream_.read(buffer, 4095);
        buffer[n] = 0;
        printf("recv: %s\n", buffer);

        return 1;
    }

    int handle_write() {
        return 1;
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
};

int main( int argc, char *argv[] )
{
    printf("start===========\n");
    nadia::InetAddress inet("6000", true, false);
    struct addrinfo *result = inet.get();
    if(NULL == result) {
        printf("no inet\n");
        //error
        return -1;
    }

    printf("stream ===========\n");
    nadia::stream s;
    if (false == s.create(inet, true)) {
        //error
        return -1;
    }

    nadia::dispatcher<nadia::epoll_dispatcher> poller; 
    nadia::acceptor<nadia::epoll_dispatcher, EchoHandler> acceptor_(s.get_handle(), &poller);
    poller.register_handler(&acceptor_, nadia::READ_EVENT);
    for(;;) {
        poller.handle_events();
    }
    return 0;
}
