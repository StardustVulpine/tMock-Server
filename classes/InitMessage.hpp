//
// Created by stardustvulpine on 1/11/26.
//

#pragma once
#include "BaseMessage.hpp"

namespace tmockserver::messages {
    class InitMessage : public BaseMessage {
    public:
        InitMessage(std::stringstream stream);

        ~InitMessage() override = default;

        void Print() const override;
        static constexpr std::size_t Size() {
            return BaseMessage::Size() + sizeof(textSize) + MAX_TEXT_LENGTH;
        }

    private:
        static constexpr std::size_t MAX_TEXT_LENGTH = 11;
        char textSize{};
        char textContent[MAX_TEXT_LENGTH + 1]{};

    };
} // tmockserver::messages