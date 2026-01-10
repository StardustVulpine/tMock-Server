//
// Created by stardustvulpine on 1/10/26.
//

#pragma once

struct init_message {
    short int msg_size;
    char msg_type;
    char payload_size;
};

struct error_message {
    short int msg_size;
    char msg_type;
    char msg_type2 = 0x2;
    char payload_size;
    char payload_msg[128];
};