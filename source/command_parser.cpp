#include <command_parser.h>
#include <thread>
#include <version.h>

/**
 * @brief Парсер команд
 * 
 * @param args - команды и параметры
 */
void CommandParser::parse(const std::vector<std::string>& args)
{
    unsigned numberOfThreads;
    std::vector<std::string> pathToImage;
    boost::program_options::options_description desc("options");
    desc.add_options()
        // Команды:
        ("threads,t", boost::program_options::value<unsigned>(&numberOfThreads)->default_value(0), "number of threads.\n") // Кол-во потоков
        ("image,i", boost::program_options::value<std::vector<std::string>>(&pathToImage), "path to image.\n") // Путь к файлу
        ("version,v", "print version number and exit.\n") // Версия
        ("help,h", "produce help message.\n");
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

        _outputMessage = VERSION.data();
        return;
    }

    checkingNumberOfThreads(numberOfThreads);
    checkingVectorPathToImage(pathToImage);

    setConfig(numberOfThreads, pathToImage);
}

void CommandParser::parse(const std::string& arg)
{
    return parse(boost::program_options::split_unix(arg));
}

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
    const auto maxNumberOfThreads = std::thread::hardware_concurrency() - 1;
    if (numberOfThreads > maxNumberOfThreads) {
        throw std::runtime_error("invalid option '--threads', maximum value is " + std::to_string(maxNumberOfThreads));
    }
}

/**
 * @brief Проверка вектора файлов
 * 
 * @param pathToImage входной вектор файлов
 */
void CommandParser::checkingVectorPathToImage(const std::vector<std::string>& pathToImage) const
{
    if (pathToImage.empty()) {
        throw std::runtime_error("no image files");
    }
}

void CommandParser::setConfig(unsigned numberOfThreads, const std::vector<std::string>& pathToImage)
{
    _config.numberOfThreads = (numberOfThreads == 0) ? (std::thread::hardware_concurrency() - 1) : numberOfThreads;
    for (const auto& pathToImageItem : pathToImage) {
        _config.pathToImage.insert(pathToImageItem);
    }
}