//
// Created by stardustvulpine on 1/11/26.
//

#pragma once

#include <sstream>


namespace tmockserver::messages {
    class BaseMessage {
    public:
        explicit BaseMessage(std::stringstream& stream);

        virtual ~BaseMessage() = default;

        virtual void Print() const;
    protected:
        static constexpr std::size_t Size() {
            return sizeof(size) + sizeof(type);
        }
    private:
        short int size{};
        char type{};

    };
} // tmockserver::messages