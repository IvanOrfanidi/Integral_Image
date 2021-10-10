#pragma once

#include <boost/program_options.hpp>

#include <config.h>

/**
 * @brief Класс Парсер команд
 * 
 */
class CommandParser {
public:
    void parse(Config& config, const std::vector<std::string>& arg);
    void parse(Config& config, const std::string& arg);
    void parse(Config& config, int argc, char* argv[]);

    /**
     * @brief Получение выходного сообщения
     * 
     * @return std::string - сообщение
     */
    std::string getOutputMessage() const noexcept;

private:
    void checkingNumberOfThreads(unsigned& numberOfThreads) const;
    void checkingVectorPathToImage(const std::vector<std::string>& pathToImage) const;

    std::string _outputMessage;
};