#pragma once

#include <functional>
#include <mutex>
#include <string>
#include <vector>

class Config {
public:
    static Config& instance();

    Config(const Config&) = delete;
    Config& operator=(Config&) = delete;

    template <class StreamType>
    friend StreamType& operator<<(StreamType& stream, const Config& config)
    {
        stream << "Number of threads: " << config._numberOfThreads << '\n';
        stream << "Images:\n";
        for (const auto& pathToImageItem : config._pathToImage) {
            stream << "  <" << pathToImageItem << ">\n";
        }
        return stream;
    }

    void setConfig(unsigned numberOfThreads, std::vector<std::string>& pathToImage);

    void setNumberOfThreads(unsigned numberOfThreads);

    unsigned getNumberOfThreads() const;

    void getPathToImage(std::vector<std::string>& pathToImage) const;

private:
    Config() = default;

    unsigned _numberOfThreads;
    std::vector<std::string> _pathToImage;
    mutable std::mutex _mtx;
};