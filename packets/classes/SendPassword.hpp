//
// Created by stardustvulpine on 1/19/26.
//

#pragma once
#include "BaseMessage.hpp"

namespace tmockserver::packets {
    class SendPassword : public BaseMessage {
    public:
        SendPassword(std::size_t msgSize, std::unique_ptr<std::byte[]>(&buffer), const networking::Socket& client_socket);

        ~SendPassword() override = default;

        void Print() const override;

        std::string Content() {
            return m_passwordContent;
        }

    private:
        char m_passwordSize{};
        std::string m_passwordContent{};

    };
} // tmockserver