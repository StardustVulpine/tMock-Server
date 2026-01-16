//
// Created by stardustvulpine on 15/1/26.
//

#pragma once


#include <TextModes.h>

#include "BaseMessage.hpp"

namespace tmockserver::messages {
    class FatalErrorMessage : public BaseMessage {
    public:
        FatalErrorMessage(TextModes textMode, std::string_view text);
        ~FatalErrorMessage() override = default;

        void Print() const override;
        std::pair<std::unique_ptr<char[]>, size_t> GetContent();

    private:
        unsigned char m_networkTextMode{};
        unsigned char m_textSize{};
        std::string m_textContent{};

    };
} // tmockserver