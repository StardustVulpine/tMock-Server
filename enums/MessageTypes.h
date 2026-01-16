//
// Created by stardustvulpine on 15/1/26.
//

#pragma once

#include <type_traits>
#include <cstddef>

namespace tmockserver {
    // In HEX byte values
    enum class MessageTypes : std::underlying_type_t<std::byte> {
        CONNECT_REQUEST = 0x01,          // Client -> Server
        FATAL_ERROR = 0x02,              // Server -> Client
        CONNECTION_APPROVED = 0x03,      // Server -> Client

        /* Some other messages here will be added later */

        REQUEST_PASSWORD = 0x25,        // Server -> Client
        LOGIN_WITH_PASSWORD = 0x26,     // Client -> Server
    };
}