#pragma once
#include <filesystem>
#include "oral/sinks/abstract_sink.hpp"

namespace oral {

enum class FileSinkLogLevel { DEBUG, INFO, WARN, ERROR, FATAL, OFF };

class FileSink : public AbstractSink<FileSink, FileSinkLogLevel> {
    public:
        FileSink(const std::filesystem::path& path) : AbstractSink<FileSink, FileSinkLogLevel>(), file_path(path) {}

        void process_log(FileSinkLogLevel level, std::string&& str) override { this->queue.push(std::move(str)); }
    private:
        std::filesystem::path file_path;
};

}; // namespace oral

using oral::FileSinkLogLevel;