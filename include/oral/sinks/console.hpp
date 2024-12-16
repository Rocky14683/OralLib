#pragma once

#include "abstract_sink.hpp"

namespace oral {

enum class ConsoleLogLevel { DEBUG, INFO, WARN, ERROR, FATAL, OFF };

class Console : public AbstractSink<Console, ConsoleLogLevel> {
    public:
        Console() : AbstractSink<Console, ConsoleLogLevel>() {}

        static std::shared_ptr<Console> get_instance() {
            std::call_once(static_flag, [&]() { instance = std::make_shared<Console>(); });
            return instance;
        }

        void process_log(ConsoleLogLevel level, std::string&& str) override {
            this->queue.push(std::move(str));
        }
    private:
        static std::once_flag static_flag;
        static std::shared_ptr<Console> instance;
};

std::once_flag Console::static_flag {};
std::shared_ptr<Console> Console::instance = Console::get_instance();

}; // namespace oral

using oral::ConsoleLogLevel;