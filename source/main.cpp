#include <thread>

#include <boost/circular_buffer.hpp>
#include <boost/program_options.hpp>

#include <command_parser.h>
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
            MSG(msg);
            return EXIT_SUCCESS;
        }

        // cv::Mat m = (cv::Mat_<uint8_t>(3, 2) << 0, 1, 2, 3, 4, 5);
        // DEB_MSG(m);
        // cv::Mat integ = integral(m);
        // DEB_MSG(integ);

        Config config = commandParser.getConfig();
        DEB_MSG(config);

        MultithreadedIntegral multithreadedIntegral(std::move(config));

        multithreadedIntegral.execute();

    } catch (const std::exception& exception) {
        ERR_MSG("error: " << exception.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
