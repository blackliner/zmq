#include <iostream>
#include <unistd.h>
#include <zmq.hpp>

// When a SUB socket binds to an address then a PUB socket connects to the
// SUB socket, the first subscription seems to be dropped.
const bool PUB_CONNECTS = false;

int main(int argc, char *argv[])
{
    void *context = zmq_ctx_new();
    void *pub = zmq_socket(context, ZMQ_PUB);
    void *sub = zmq_socket(context, ZMQ_SUB);

    // Make one of PUB or SUB sockets be a server.
    void *server = 0;
    void *client = 0;
    if (PUB_CONNECTS)
    {
        server = sub;
        client = pub;
    }
    else
    {
        server = pub;
        client = sub;
    }
    zmq_bind(server, "tcp://127.0.0.1:5932");
    zmq_connect(client, "tcp://127.0.0.1:5932");

    // Start to subscribe "hello".
    zmq_setsockopt(sub, ZMQ_SUBSCRIBE, "hello", 5);
    usleep(1000);

    // Publish and receive a message.
    zmq_send(pub, "hello world", 11, 0);
    std::cout << "SUB is waiting for an incoming message..." << std::endl;
    char recv_buf[40] = {0};
    int n_bytes = zmq_recv(sub, recv_buf, 40, 0);
    if (n_bytes > 0)
    {
        std::cout << recv_buf << std::endl;
    }

    // Finalize.
    zmq_close(sub);
    zmq_close(pub);
    zmq_ctx_destroy(context);
    return 0;
}