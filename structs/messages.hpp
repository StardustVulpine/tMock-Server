//
// Created by stardustvulpine on 1/10/26.
//

#pragma once

namespace tmockserver {
    struct init_message {
        short int size;
        char type;
        char payload_size;
    };

    struct error_message {
        short int msg_size{};
        char msg_type{};
        char network_text_mode{};
        char payload_size{};
        char payload_msg[128]{};
    };
}