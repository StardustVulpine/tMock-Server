//
// Created by stardustvulpine on 18/2/26.
//

#pragma once
#include <format>
#include <string>
#include <iostream>
#include <chrono>

namespace tmockserver::Console
{
    class Log
    {
        struct Color
        {
            std::string GREEN = "\033[38;2;0;255;1m";
            std::string YELLOW = "\033[38;2;255;191;0m";
            std::string ORANGE = "\033[38;2;204;85;0m";
            std::string RED = "\033[38;2;220;20;60m";
            std::string PURPLE = "\033[38;2;255;0;255m";
            std::string BLUE = "\033[38;2;0;255;255m";
            std::string RESET = "\033[0m";
        };

        public:
        template<class... Args> static void Print(std::format_string<Args...> msg, Args&&... args)
        {
            std::string message = std::format(msg, std::forward<Args>(args)...);
            std::println(std::cout, "{} {}", Time(), message);
        }

        template<class... Args> static void Debug(std::format_string<Args...> msg, Args&&... args)
        {
            std::string message = std::format(msg, std::forward<Args>(args)...);
            std::println(std::cout, "{}{} [DEBUG] {}{}", color.ORANGE, Time(), message, color.RESET);
        }

        template<class... Args> static void Info(std::format_string<Args...> msg, Args&&... args)
        {
            std::string message = std::format(msg, std::forward<Args>(args)...);
            std::println(std::cout, "{}{} [INFO] {}{}", color.GREEN, Time(), message, color.RESET);
        }

        template<class... Args> static void Warning(std::format_string<Args...> msg, Args&&... args)
        {
            std::string message = std::format(msg, std::forward<Args>(args)...);
            std::println(std::cout, "{}{} [WARNING] {}{}", color.YELLOW, Time(), message, color.RESET);
        }

        template<class... Args> static void Error(std::format_string<Args...> msg, Args&&... args)
        {
            std::string message = std::format(msg, std::forward<Args>(args)...);
            std::println(std::cout, "{}{} [ERROR] {}{}", color.RED, Time(), message, color.RESET);
        }

        private:
        // Declaration of the static member. The definition will be in Log.cpp.
        static const Color color;

        static std::string Time()
        {
            const auto utc_now{std::chrono::system_clock::now()};
            const auto time = std::chrono::current_zone()->to_local(utc_now);

            return std::vformat("{}", std::make_format_args(time));
        }
    };
    const Log::Color Log::color = Color();
}
