//
// Created by stardustvulpine on 1/16/26.
//

#pragma once

//Packets
#include "../src/ConnectRequest.hpp"        // 0x01
#include "../src/FatalError.hpp"            // 0x02
#include "../src/ConnectionApproved.hpp"    // 0x03
#include "../src/RequestPassword.hpp"       // 0x25
#include "../src/SendPassword.hpp"          // 0x26

// Enums
#include "../enums/PacketType.hpp"
#include "../enums/NetworkTextMode.hpp"
