#pragma once

#include <set>
#include <string>

/**
 * @brief Класс конфигурации
 * 
 */
struct Config {
    unsigned numberOfThreads; ///< Кол-во потоков
    std::set<std::string> pathsToImages; ///< Перечисление файлов
};

/**
 * @brief Вывод в поток конфигурации
 * 
 * @tparam StreamType - тип потока
 * @param stream - поток
 * @param config - класс конфигурации
 * @return StreamType& - вывод
 */
template <class StreamType>
StreamType& operator<<(StreamType& stream, const Config& config)
{
    stream << "Number of threads: " << config.numberOfThreads << '\n';
    stream << "Images:\n";
    for (const auto& pathToImage : config.pathsToImages) {
        stream << "  <" << pathToImage << ">\n";
    }
    return stream;
}