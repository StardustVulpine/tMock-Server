//
// Created by stardustvulpine on 1/11/26.
//

#pragma once

#include <memory>
#include <sstream>
#include <MessageTypes.h>

namespace tmockserver::messages {
    class BaseMessage {
    public:
        explicit BaseMessage(std::stringstream& stream);
        BaseMessage(std::size_t size, MessageTypes type);


        virtual ~BaseMessage() = default;

        virtual void Print() const;
        std::unique_ptr<char[]> CreateBuffer();

    protected:
        static constexpr std::size_t Size() {
            return sizeof(m_size) + sizeof(m_type);
        }
    private:
        short int m_size{};
        char m_type{};

    };
} // tmockserver::messages