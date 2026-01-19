//
// Created by stardustvulpine on 1/11/26.
//

#pragma once
#include "BaseMessage.hpp"
#include "MessageTypes.h"

namespace tmockserver::messages {
    class ConnectRequest : public BaseMessage {
    public:
        ConnectRequest(std::size_t msgSize, std::unique_ptr<std::byte[]>(&buffer), const Socket& client_socket);
        ConnectRequest(std::size_t msgSize, std::size_t txtSize, std::string  text);

        ~ConnectRequest() override = default;

        void Print() const override;

    private:
        char m_textSize{};
        std::string m_textContent{};

    };
} // tmockserver::messages