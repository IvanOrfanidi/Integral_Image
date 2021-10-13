#include <thread>

#include <boost/circular_buffer.hpp>
#include <boost/program_options.hpp>

#include <command_parser.h>
#include <file_handler.h>
#include <message.h>
#include <multithreaded_integral.h>

int main(/*int argc, char* argv[]*/)
{
    CommandParser commandParser;
    try {
        commandParser.parse("-t 2 -i img/RED.jpg -i img/24.bmp");
        const std::string msg = commandParser.getOutputMessage();
        if (!msg.empty()) {
            // Вывод версии или хелпа
            INFO(msg);
            return EXIT_SUCCESS;
        }

        std::vector<Image> partsOfImages; ///< Массив структур одноканальных матриц с номером канала и именем файла
        std::vector<Image> partsOfIntegralImages; ///< Массив структур одноканальных интегральных матриц с номером канала и именем файла

        // Получаем конфигурацию из парсера команд
        Config config = commandParser.getConfig();
        DEB_INFO(config);

        FileHandler fileHandler(std::move(config.pathsToImages));
        // Читаем данные из файлов
        fileHandler.dataRead(partsOfImages);

        MultithreadedIntegral multithreadedIntegral(config.numberOfThreads);
        // Вычисляем данные(интегральные матрицы)
        multithreadedIntegral.calculate(partsOfIntegralImages, partsOfImages);

        // Пишем данные(интегральные матрицы) в файлы
        fileHandler.dataWrite(partsOfIntegralImages);
    } catch (const std::exception& exception) {
        ERR_INFO("error: " << exception.what());
        return EXIT_FAILURE;
    }

    INFO("successful result");
    return EXIT_SUCCESS;
}
