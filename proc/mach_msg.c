#include <mach/mach.h>
#include <string.h>
#include <stdio.h>

struct Message {
    mach_msg_header_t header;
    int data;
};

int main(void) {
    mach_port_t client;
    mach_port_t server;

    struct Message message;

    // construct the header
    message.header.msgh_size = sizeof(message);
    message.header.msgh_remote_port = server;
    message.header.msgh_local_port = client;
    message.data = 124538;

    // send the message
    mach_msg(&message.header, // message header
    MACH_SEND_MSG, // sending a message
    sizeof(message), // size of message sent
    0, // maximum size of received message - unnecessary
    MACH_PORT_NULL, // name of receive port - unnecessary
    MACH_MSG_TIMEOUT_NONE, // no time outs
    MACH_PORT_NULL // no notify port
    );

    struct Message message2;

    // receive the message
    int server_rcv_msg = mach_msg(&message2.header, // message header
    MACH_RCV_MSG, // sending a message
    0, // size of message sent
    sizeof(message2), // maximum size of received message
    server, // name of receive port
    MACH_MSG_TIMEOUT_NONE, // no time outs
    MACH_PORT_NULL // no notify port
    );

    if(server_rcv_msg > 0) printf("%d", message2.data);

    return 0;
}