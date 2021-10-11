#pragma once

#include <boost/program_options.hpp>

#include <config.h>

/**
 * @brief Класс Парсер команд
 * 
 */
class CommandParser {
public:
    /**
     * @brief Парсер команд
     * 
     * @param args - команды и параметры
     */
    void parse(const std::vector<std::string>& arg);
    void parse(const std::string& arg);
    void parse(int argc, char* argv[]);


    /**
     * @brief Получить конфигурацию
     * 
     * @return Config - конфигурация
     */
    Config getConfig() const noexcept;

    /**
     * @brief Получение выходного сообщения
     * 
     * @return std::string - сообщение
     */
    std::string getOutputMessage() const noexcept;

private:
    void checkingNumberOfThreads(unsigned numberOfThreads) const;
    void checkingVectorPathToImage(const std::vector<std::string>& pathToImage) const;
    void setConfig(unsigned numberOfThreads, const std::vector<std::string>& pathToImage);

    Config _config;
    std::string _outputMessage;
};