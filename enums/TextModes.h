//
// Created by stardustvulpine on 15/1/26.
//

#pragma once

namespace tmockserver {
    enum class TextModes {
        LITERAL = 0x00,
        FORMATTABLE = 0x01,
        LOCALIZATION_KEY = 0x02,
        SUBSTITUTION = 0x03,
    };
}