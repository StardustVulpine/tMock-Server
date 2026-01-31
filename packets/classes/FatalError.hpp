//
// Created by stardustvulpine on 15/1/26.
//

#pragma once

#include "BaseMessage.hpp"
#include "../enums/NetworkTextMode.hpp"

namespace tmockserver::packets {
    class FatalError : public BaseMessage {
    public:
        FatalError(NetworkTextMode textMode, std::string_view text);
        ~FatalError() override = default;

        void Print() const override;
        void Send(const networking::Socket &socket) const override;
        [[nodiscard]] std::pair<std::unique_ptr<char[]>, size_t> GetContent() const;


    private:
        unsigned char m_networkTextMode{};
        unsigned char m_textSize{};
        std::string m_textContent{};

    };
} // tmockserver