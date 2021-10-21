#include <command_parser.h>
#include <project_version.h>
#include <thread>

/**
 * @brief Парсер команд
 * @details Перегруженная функция
 * 
 * @param args - массив строк команд и параметров
 */
void CommandParser::parse(const std::vector<std::string>& args)
{
    unsigned numberOfThreads;
    std::vector<std::string> pathsToImages;
    boost::program_options::options_description desc("options");
    desc.add_options()
        // Команды:
        ("threads,t", boost::program_options::value<unsigned>(&numberOfThreads)->default_value(0), "number of threads.") // Кол-во потоков
        ("image,i", boost::program_options::value<std::vector<std::string>>(&pathsToImages), "path to image.") // Путь к файлу
        ("version,v", "print version number and exit.") // Версия
        ("help,h", "produce help message.");
    boost::program_options::variables_map options;

    boost::program_options::store(boost::program_options::command_line_parser(args).options(desc).run(), options);
    boost::program_options::notify(options);

    if (options.count("help")) {
        std::stringstream ss;
        ss << desc;
        _outputMessage = ss.str();
        return;
    }
    if (options.count("version")) {

        _outputMessage = "version: " + std::string(PROJECT_VERSION);
        return;
    }

    checkingNumberOfThreads(numberOfThreads);
    checkingVectorPathToImage(pathsToImages);

    setConfig(numberOfThreads, pathsToImages);
}

/**
 * @brief Парсер команд
 * @details Перегруженная функция, команды ввиде строки ("-t 2 -i img/RED.jpg")
 * 
 * @param arg - строка с командами и параметрами
 */
void CommandParser::parse(const std::string& arg)
{
    return parse(boost::program_options::split_unix(arg));
}

/**
 * @brief Парсер команд
 * @details Перегруженная функция
 * 
 * @param argc - кол-во аргументов
 * @param argv - команды и параметры
 */
void CommandParser::parse(int argc, char* argv[])
{
    const std::vector<std::string> vArg(argv + 1, argv + argc);
    return parse(vArg);
}

/**
 * @brief Получить конфигурацию
 * 
 * @return Config - конфигурация
 */
Config CommandParser::getConfig() const noexcept
{
    return _config;
}

/**
 * @brief Получение выходного сообщения
 * 
 * @return std::string - сообщение
 */
std::string CommandParser::getOutputMessage() const noexcept
{
    return _outputMessage;
}

/**
 * @brief Проверка кол-ва потоков на корректность
 * 
 * @param numberOfThreads кол-во потоков
 */
void CommandParser::checkingNumberOfThreads(unsigned numberOfThreads) const
{
    const unsigned maxNumberOfThreads = std::thread::hardware_concurrency();
    if (maxNumberOfThreads != 0 && numberOfThreads > maxNumberOfThreads - 1) {
        throw std::runtime_error("invalid option '--threads', maximum value is " + std::to_string(maxNumberOfThreads));
    }
}

/**
 * @brief Проверка вектора файлов
 * 
 * @param pathsToImages входной вектор файлов
 */
void CommandParser::checkingVectorPathToImage(const std::vector<std::string>& pathsToImages) const
{
    if (pathsToImages.empty()) {
        throw std::runtime_error("no image files");
    }
}

/**
 * @brief Установка конфигурации
 * 
 * @param numberOfThreads - кол-во потоков
 * @param pathsToImages - контейнер с путями к файлам
 */
void CommandParser::setConfig(unsigned numberOfThreads, const std::vector<std::string>& pathsToImages)
{
    const unsigned maxNumberOfThreads = (std::thread::hardware_concurrency() != 0) ? (std::thread::hardware_concurrency() - 1) : 1;
    _config.numberOfThreads = (numberOfThreads == 0) ? maxNumberOfThreads : numberOfThreads;
    for (const auto& pathToImageItem : pathsToImages) {
        _config.pathsToImages.insert(pathToImageItem);
    }
}