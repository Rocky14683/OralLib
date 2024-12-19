#pragma once
#include <filesystem>
#include <utility>
#include <fstream>
#include "oral/sinks/abstract_sink.hpp"

namespace oral {

enum class FileSinkLogLevel { DEBUG, INFO, WARN, ERROR, FATAL, OFF };

class FileSink : public AbstractSink<FileSink, FileSinkLogLevel> {
    public:
        using AbstractSink<FileSink, FileSinkLogLevel>::AbstractSink;
        friend class AbstractSink<FileSink, FileSinkLogLevel>;

        FileSink(const std::filesystem::path& path) : AbstractSink<FileSink, FileSinkLogLevel>(), file_path(path) {}

        void process_log(FileSinkLogLevel level, std::string&& str) noexcept override {
            this->queue.push(std::move(str));
        }
    private:
        std::filesystem::path file_path;
        std::ofstream file;
};

}; // namespace oral

using oral::FileSinkLogLevel;