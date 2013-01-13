#include    <stdio.h>
#include    <string.h>
#include    "stream.h"
#include    "handler.h"
#include    "dispatcher.h"
#include    "epoll_dispatcher.h"
#include    "acceptor.h"
#include    "echo_handler.h"

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

    nadia::epoll_dispatcher poller; 
    nadia::acceptor<EchoHandler> acceptor_(s.get_handle(), &poller);
    poller.register_handler(&acceptor_, nadia::READ_EVENT);
    for(;;) {
        poller.handle_events();
    }
    return 0;
}
