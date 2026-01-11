//
// Created by stardustvulpine on 1/11/26.
//
#pragma once

#include "../structs/messages.h"
#include <string>

namespace tmockserver::messagelogger {
    class Log {
        public:
        Log() = default;

        static void InitMessage(init_message msg, std::string payload);

    };
} // tmockserver