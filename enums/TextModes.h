//
// Created by stardustvulpine on 15/1/26.
//

#pragma once

namespace tmockserver {
    enum class TextModes : std::underlying_type_t<std::byte> {
        LITERAL = 0x00,
        FORMATTABLE = 0x01,
        LOCALIZATION_KEY = 0x02,
        SUBSTITUTION = 0x03,
    };

    template<typename T, typename S>
    requires std::is_enum_v<S>
    constexpr T enumTo (S type) {
        return static_cast<T>(type);
    }
}