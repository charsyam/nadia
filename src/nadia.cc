#include    "nadia_stream.h"

int main( int argc, char *argv[] )
{
    nadia::InetAddress inet("8080", true, false);
    struct addrinfo *result = inet.get();
    if(NULL == result) {
        //error
        return -1;
    }

    nadia::stream s;
    if (false == s.create(inet, true)) {
        //error
        return -1;
    }

    return 0;
}
