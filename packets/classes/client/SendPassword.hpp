//
// Created by stardustvulpine on 1/19/26.
//

#pragma once
#include "../BasePacket.hpp"

namespace tmockserver::packets {
    class SendPassword : public BasePacket {
    public:
        SendPassword(std::size_t msgSize, std::unique_ptr<std::byte[]>(&buffer), const networking::Socket& client_socket);

        ~SendPassword() override = default;

        void Print() const override;

        std::string Content() {
            return m_passwordContent;
        }

    private:
        std::byte m_passwordSize{};
        std::string m_passwordContent{};

    };
} // tmockserver