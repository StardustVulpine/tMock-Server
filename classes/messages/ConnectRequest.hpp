//
// Created by stardustvulpine on 1/11/26.
//

#pragma once
#include "BaseMessage.hpp"
#include "MessageTypes.h"

namespace tmockserver::messages {
    class ConnectRequest : public BaseMessage {
    public:
        ConnectRequest(std::stringstream stream);
        ConnectRequest(std::size_t msgSize, std::unique_ptr<std::byte[]>(&buffer), const Socket& client_socket);
        ConnectRequest(std::size_t msgSize, std::size_t txtSize, std::string  text);

        ~ConnectRequest() override = default;

        [[nodiscard]]
        static ConnectRequest Get(const Socket &socket);
        void Print() const override;
        static constexpr std::size_t Size() {
            return BaseMessage::Size() + sizeof(m_textSize) + MAX_TEXT_LENGTH;
        }

    private:
        static constexpr std::size_t MAX_TEXT_LENGTH = 11;
        char m_textSize{};
        std::string m_textContent{};

    };
} // tmockserver::messages