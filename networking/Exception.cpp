//
// Created by stardustvulpine on 1/10/26.
//

#include "Exception.hpp"

namespace tmockserver {
    Exception::Exception(const std::string& message) : std::runtime_error(message) {

    }

} // tmockserver