//
// Created by stardustvulpine on 1/19/26.
//

#pragma once
#include "BasePacket.hpp"

namespace tmockserver::packets {
    class SendPassword : public BasePacket {
    public:
        SendPassword(std::size_t msgSize, std::unique_ptr<std::byte[]>(&buffer), const net::Socket& client_socket);

        ~SendPassword() override = default;

        void Print() const override;

        std::string Content() {
            return m_passwordContent;
        }

    private:
        std::byte m_passwordSize{};
        std::string m_passwordContent{};

        [[nodiscard]] std::unique_ptr<std::byte[]> GetPacketContent(const std::unique_ptr<std::byte[]> buffer) const override
        {
            std::byte* ptr = buffer.get();
            (void)ptr; // :C
            return nullptr;
        }

    };
} // tmockserver