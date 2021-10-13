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
     * @details Перегруженная функция
     * 
     * @param args - массив строк команд и параметров
     */
    void parse(const std::vector<std::string>& arg);

    /**
     * @brief Парсер команд
     * @details Перегруженная функция, команды ввиде строки ("-t 2 -i img/RED.jpg")
     * 
     * @param arg - строка с командами и параметрами
     */
    void parse(const std::string& arg);

    /**
     * @brief Парсер команд
     * @details Перегруженная функция
     * 
     * @param argc - кол-во аргументов
     * @param argv - команды и параметры
     */
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
    /**
     * @brief Проверка кол-ва потоков на корректность
     * 
     * @param numberOfThreads кол-во потоков
     */
    void checkingNumberOfThreads(unsigned numberOfThreads) const;

    /**
     * @brief Проверка вектора файлов
     * 
     * @param pathsToImages входной вектор файлов
     */
    void checkingVectorPathToImage(const std::vector<std::string>& pathsToImages) const;

    /**
     * @brief Установка конфигурации
     * 
     * @param numberOfThreads - кол-во потоков
     * @param pathsToImages - контейнер с путями к файлам
     */
    void setConfig(unsigned numberOfThreads, const std::vector<std::string>& pathsToImages);

    Config _config; ///< Конфигурация
    std::string _outputMessage; ///< Выходное сообщение парсера (хелп, версия)
};