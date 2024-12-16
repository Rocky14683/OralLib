
#pragma once
#include <queue>
#include <string>
#include <format>
#include <memory>
#include <memory>
#include <mutex>
#include <type_traits>

namespace oral {

// abstract sink
// sd card
// stdout
// brain screen
template <class Derived, class Enum_log_level> class AbstractSink {

        static_assert(std::is_enum_v<Enum_log_level>, "Enum_log_level must be an enum class");

    public:
        AbstractSink() = default;
        virtual ~AbstractSink() = default;

        enum class LogLevel {};

        // log peripheral
        template <typename... Args>
        inline void log(Enum_log_level log_level, std::format_string<Args...> fmt, Args&&... args) {
            std::string log_message = this->prefix + std::format(fmt, std::forward<Args>(args)...) + this->postfix;
            static_cast<Derived*>(this)->process_log(log_level, std::move(log_message));
        }

        constexpr void set_prefix(const std::string& prefix) noexcept { this->prefix = prefix; }

        constexpr void set_postfix(const std::string& postfix) noexcept { this->postfix = postfix; }

        virtual void process_log(Enum_log_level log_level, std::string&&) = 0;
    protected:
        std::queue<std::string> queue;
        std::string prefix;
        std::string postfix;
};

} // namespace oral
