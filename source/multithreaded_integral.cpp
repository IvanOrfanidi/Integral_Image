#include <message.h>
#include <multithreaded_integral.h>

#include <array>

#include <opencv2/core.hpp>

void MultithreadedIntegral::calculateIntegralImage(std::vector<Image>& integralMatrices, const std::vector<Image>& imagesMatrices)
{
    for (const auto& partOfImage : imagesMatrices) {
        integralMatrices.push_back({ partOfImage.name, partOfImage.channel, integral(partOfImage.matrix) });
    }
}

MultithreadedIntegral::MultithreadedIntegral(Config config) noexcept
    : _config(std::move(config))
{
}

void MultithreadedIntegral::execute()
{
    MapThreeChannelMatrices threeChannelMatrices;
    {
        std::array<cv::Mat, 3> channels;
        channels[0] = (cv::Mat_<uint8_t>(3, 2) << 0, 1, 2, 3, 4, 5);
        channels[1] = (cv::Mat_<uint8_t>(3, 2) << 0, 1, 2, 3, 4, 6);
        threeChannelMatrices.insert({ "1", std::move(channels) });
    }
    {
        std::array<cv::Mat, 3> channels;
        channels[1] = (cv::Mat_<uint8_t>(3, 2) << 0, 1, 2, 3, 4, 5);
        channels[2] = (cv::Mat_<uint8_t>(3, 2) << 0, 1, 2, 3, 4, 6);
        threeChannelMatrices.insert({ "2", std::move(channels) });
    }
    //fillingInThreeChannelMatrices(threeChannelMatrices);

    std::vector<Image> partsOfImages;
    fillingInQueueMatrices(partsOfImages, threeChannelMatrices);

    std::vector<Image> partsOfIntegralImages;
    calculate(partsOfIntegralImages, partsOfImages);

    for (const auto& partOfIntegralImage : partsOfIntegralImages) {
        DEB_MSG(partOfIntegralImage);
    }
}

/**
 * @brief Заполнение мепа одноканальными матрицами
 * 
 * @param threeChannelMatrices - выходной map с одноканальными матрицами
 */
void MultithreadedIntegral::fillingInThreeChannelMatrices(std::map<std::string, std::array<cv::Mat, 3>>& threeChannelMatrices) const
{
    for (const auto& pathToImageItem : _config.pathToImage) {
        cv::Mat image = cv::imread(pathToImageItem);
        if (image.empty()) {
            ERR_MSG("couldn't open or find image file: " + pathToImageItem);
            continue;
        }

        std::array<cv::Mat, 3> channels;
        cv::split(image, channels);
        threeChannelMatrices.insert({ pathToImageItem, std::move(channels) });
    }
}

void MultithreadedIntegral::fillingInQueueMatrices(std::vector<Image>& partsOfImages,
    const MapThreeChannelMatrices& threeChannelMatrices) const
{
    for (const auto& threeChannelMatrix : threeChannelMatrices) {
        for (uint8_t channel = 0; channel < threeChannelMatrix.second.size(); ++channel) {
            partsOfImages.push_back({ threeChannelMatrix.first, channel, threeChannelMatrix.second[channel] });
        }
    }
}

void MultithreadedIntegral::calculate(std::vector<Image>& partsOfIntegralImages, const std::vector<Image>& partsOfImages)
{
    unsigned countThreads = 0;
    std::vector<std::vector<Image>> partsOfImagesForThreads(_config.numberOfThreads);
    for (const auto& partOfImage : partsOfImages) {
        partsOfImagesForThreads[countThreads].push_back(partOfImage);
        countThreads = (++countThreads >= _config.numberOfThreads) ? 0 : countThreads;
    }

    std::vector<std::vector<Image>> partsOfIntegralImagesForThreads(_config.numberOfThreads);
    _threads.resize(_config.numberOfThreads);
    for (countThreads = 0; countThreads < _config.numberOfThreads; ++countThreads) {
        const auto& imagesMatrices = partsOfImagesForThreads[countThreads];
        auto& integralMatrices = partsOfIntegralImagesForThreads[countThreads];
        _threads[countThreads] = std::thread(calculateIntegralImage, std::ref(integralMatrices), std::ref(imagesMatrices));
    }

    waitingForEndOfThreads();

    for (const auto& partOfIntegralImageForThreads : partsOfIntegralImagesForThreads) {
        std::copy(partOfIntegralImageForThreads.cbegin(), partOfIntegralImageForThreads.cend(), std::back_inserter(partsOfIntegralImages));
    }
}

void MultithreadedIntegral::waitingForEndOfThreads()
{
    for (auto& entry : _threads) {
        entry.join();
    }
}