#include <config.h>

Config& Config::instance()
{
    static Config config;
    return config;
}

void Config::setConfig(unsigned numberOfThreads, std::vector<std::string>& pathToImage)
{
    std::lock_guard<std::mutex> lock(_mtx);
    _numberOfThreads = numberOfThreads;
    _pathToImage = pathToImage;
}

void Config::setNumberOfThreads(unsigned numberOfThreads)
{
    std::lock_guard<std::mutex> lock(_mtx);
    _numberOfThreads = numberOfThreads;
}

unsigned Config::getNumberOfThreads() const
{
    std::lock_guard<std::mutex> lock(_mtx);
    return _numberOfThreads;
}

void Config::getPathToImage(std::vector<std::string>& pathToImage) const
{
    std::lock_guard<std::mutex> lock(_mtx);
    pathToImage = _pathToImage;
}