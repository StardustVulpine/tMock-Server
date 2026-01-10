//
// Created by stardustvulpine on 1/10/26.
//

#pragma once
#include <stdexcept>

namespace tmockserver {
    class Exception : public std::runtime_error {
        public:
        Exception(std::string message);
    };
} // tmockserver
