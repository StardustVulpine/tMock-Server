//
// Created by stardustvulpine on 18/2/26.
//

#pragma once
#include <format>
#include <string>
#include <iostream>
#include <chrono>

namespace stardustvulpine::Console::Logger
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

        enum class Severity
        {
            NONE_L = 0,
            INFO_L,
            DEBUG_L,
            WARNING_L,
            ERROR_L
        };

        public:
        template<class... Args> static void Print(const std::string_view msg, Args&&... args)
        {
            const std::string message = std::vformat(msg, std::make_format_args(args...));
            PrintLog(Severity::NONE_L, message);
        }

        template<class... Args> static void Debug(std::format_string<Args...> msg, Args&&... args)
        {
            const std::string message = std::format(msg, std::forward<Args>(args)...);
            PrintLog(Severity::DEBUG_L, message);
        }

        template<class... Args> static void Info(std::format_string<Args...> msg, Args&&... args)
        {
            const std::string message = std::format(msg, std::forward<Args>(args)...);
            PrintLog(Severity::INFO_L, message);
        }

        template<class... Args> static void Warning(std::format_string<Args...> msg, Args&&... args)
        {
            const std::string message = std::format(msg, std::forward<Args>(args)...);
            PrintLog(Severity::WARNING_L, message);
        }

        template<class... Args> static void Error(std::format_string<Args...> msg, Args&&... args)
        {
            const std::string message = std::format(msg, std::forward<Args>(args)...);
            PrintLog(Severity::ERROR_L, message);
        }

        private:
        // Declaration of the static member. The definition will be in Log.cpp.
        static const Color color;

        static void PrintLog(const Severity severity, const std::string& msg)
        {
            std::string col;
            std::string level;
            switch (severity)
            {
                case Severity::DEBUG_L:
                    col = color.ORANGE;
                    level = "DEBUG";
                    break;
                case Severity::ERROR_L:
                    col = color.RED;
                    level = "ERROR";
                    break;
                case Severity::INFO_L:
                    col = color.GREEN;
                    level = "INFO";
                    break;
                case Severity::WARNING_L:
                    col = color.YELLOW;
                    level = "WARNING";
                    break;
                case Severity::NONE_L:
                    col = color.RESET;
                    level = "";
                    break;
            }

            std::println(std::cout,"{}[{}] {}: {}{}", col, Time(), level, msg, color.RESET);
        }

        static std::string Time()
        {
            const auto utc_now{std::chrono::system_clock::now()};
            const auto time = std::chrono::current_zone()->to_local(utc_now);

            return std::vformat("{}", std::make_format_args(time));
        }
    };
    inline const Log::Color Log::color = Color();
}
