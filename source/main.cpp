#include <thread>

#include <boost/circular_buffer.hpp>
#include <boost/program_options.hpp>

#include <opencv2/dnn.hpp>
#include <opencv2/opencv.hpp>

#include <command_parser.h>
#include <message.h>

int main(/*int argc, char* argv[]*/)
{
    Config& config = Config::instance();
    CommandParser commandParser;
    try {
        commandParser.parse(config, "-t 8 -i img/RED.BMP");

        const std::string msg = commandParser.getOutputMessage();
        if (!msg.empty()) {
            // Вывод информации(версии, хелпа)
            MSG(msg);
            return EXIT_SUCCESS;
        }
        DEB_MSG(config);

        std::vector<std::string> pathToImage;
        config.getPathToImage(pathToImage);
        for (auto& image : pathToImage) {
            cv::Mat src = cv::imread(image);
            if (src.empty()) {
                ERR_MSG("couldn't open OSD file: " + image);
            }

            cv::imshow(image, src);
            while (cv::waitKey(100) != 27) {
            }
        }

    } catch (const std::exception& exception) {
        ERR_MSG("error: " << exception.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
