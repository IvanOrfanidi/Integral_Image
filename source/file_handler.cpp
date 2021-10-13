#include <file_handler.h>

FileHandler::FileHandler(const std::set<std::string> pathsToImages)
    : _pathsToImages(std::move(pathsToImages))
{
}

/**
 * @brief Чтение файлов
 * 
 * @param partsOfImages - массив структуры одноканальных матриц с номером канала и именем файла
 */
void FileHandler::read(std::vector<Image>& partsOfImages) const
{
    MapImages images; // Список изображений(3-х канальных матриц) с именем файла
    // for (const auto& pathToImage : _config._pathsToImages) {
    //     cv::Mat image = cv::imread(pathToImage);
    //     if (image.empty()) {
    //         ERR_MSG("couldn't open or find image file: " + pathToImage);
    //         continue;
    //     }

    //     ThreeMatrixArray channels; // BGR
    //     cv::split(image, channels);
    //     images.insert({ pathToImage, std::move(channels) });
    // }

    {
        ThreeMatrixArray channels;
        channels[0] = (cv::Mat_<uint8_t>(3, 2) << 0, 1, 2, 3, 4, 5);
        channels[1] = (cv::Mat_<uint8_t>(3, 2) << 0, 1, 2, 3, 4, 6);
        images.insert({ "1", std::move(channels) });
    }
    {
        ThreeMatrixArray channels;
        channels[1] = (cv::Mat_<uint8_t>(3, 2) << 0, 1, 2, 3, 4, 5);
        channels[2] = (cv::Mat_<uint8_t>(3, 2) << 0, 1, 2, 3, 4, 6);
        images.insert({ "2", std::move(channels) });
    }

    fillingInPartsOfImages(partsOfImages, images);
}

/**
 * @brief Заполнение массив с структурами изображений
 * 
 * @param partsOfImages - выходной массив с структурами изображений
 * @param images - входной map с файлами изображений
 */
void FileHandler::fillingInPartsOfImages(std::vector<Image>& partsOfImages, const MapImages& images) const
{
    for (const auto& image : images) {
        for (uint8_t channel = 0; channel < image.second.size(); ++channel) {
            partsOfImages.push_back({ image.first, channel, image.second[channel] });
        }
    }
}

void FileHandler::write(const std::vector<Image>& partsOfIntegralImages) const
{
    // for (const auto& pathToImage : _pathsToImages)
    // {
    //     for()
    // }
}