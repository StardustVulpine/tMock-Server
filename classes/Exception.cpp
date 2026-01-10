//
// Created by stardustvulpine on 1/10/26.
//

#include "Exception.h"

namespace tmockserver {
    Exception::Exception(std::string message) : std::runtime_error(message) {

    }

} // tmockserver