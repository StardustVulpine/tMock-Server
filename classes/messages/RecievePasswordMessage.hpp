//
// Created by stardustvulpine on 1/19/26.
//

#pragma once
#include "BaseMessage.hpp"

namespace tmockserver::messages {
    class RecievePasswordMessage : public BaseMessage {
    public:
        RecievePasswordMessage(std::size_t msgSize, std::unique_ptr<std::byte[]>(&buffer), const Socket& client_socket);

        ~RecievePasswordMessage() override = default;

        void Print() const override;

        std::string Content() {
            return m_passwordContent;
        }

    private:
        char m_passwordSize{};
        std::string m_passwordContent{};

    };
} // tmockserver