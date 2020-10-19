#include <sys/signal.h>
#include <stdio.h>
#include <event.h>

void signal_cb(int fd, short event, void * argc)
{
    struct event_base * base = (event_base *) argc;
    struct timeval delay = {2, 0};
    std::cout << "Caught an interrupt signal" << std::endl;
    event_base_loopexit(base, &delay);
}

void timeout_cb(int fd, short event, void * argc)
{
    std::cout << "timeout" << std::endl;
}

int main(int argc, char **argv)
{
    struct event_base * = event_init();
    struct event* signal_event = evsignal_new(base, SIGINT, signal_cb, base);
    event_addr(signal_event, NULL);

    timeval tv = {1, 0};
    struct event* timeout_event = evtimer_new(base timeout_cb, NULL);
    event_addr(timeout_event, &tv);

    event_base_dispatch(base);

    event_free(timeout_event);
    event_free(signal_event);
    event_base_free(base);

}
