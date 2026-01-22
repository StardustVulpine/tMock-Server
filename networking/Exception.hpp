//
// Created by stardustvulpine on 1/10/26.
//

#pragma once
#include <stdexcept>

namespace tmockserver {
    class Exception : public std::runtime_error {
        public:
        explicit Exception(const std::string& message);
    };
} // tmockserver
