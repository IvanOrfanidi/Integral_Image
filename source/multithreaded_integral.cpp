#include <message.h>
#include <multithreaded_integral.h>

#include <array>

#include <opencv2/core.hpp>

/**
 * @brief Конструктор класса MultithreadedIntegral
 * 
 * @param config - конфигурация
 */
MultithreadedIntegral::MultithreadedIntegral(Config config) noexcept
    : _config(std::move(config))
{
}

void MultithreadedIntegral::execute()
{
    MapImages images; // Список изображений(3-х канальных матриц) с именем файла
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
    //fillingInImages(images);

    std::vector<Image> partsOfImages; // Массив структуры одноканальных матриц с номером канала и именем файла
    fillingInPartsOfImages(partsOfImages, images);

    std::vector<Image> partsOfIntegralImages; // Массив структуры одноканальных интегральных матриц с номером канала и именем файла
    calculate(partsOfIntegralImages, partsOfImages);

    for (const auto& partOfIntegralImage : partsOfIntegralImages) {
        DEB_MSG(partOfIntegralImage);
    }

    //writeToFile(partsOfIntegralImages);
}

/**
 * @brief Заполнение мепа файлами изображений
 * 
 * @param images - выходной map с файлами изображений
 */
void MultithreadedIntegral::fillingInImages(MapImages& images) const
{
    for (const auto& pathToImageItem : _config.pathToImage) {
        cv::Mat image = cv::imread(pathToImageItem);
        if (image.empty()) {
            ERR_MSG("couldn't open or find image file: " + pathToImageItem);
            continue;
        }

        ThreeMatrixArray channels; // BGR
        cv::split(image, channels);
        images.insert({ pathToImageItem, std::move(channels) });
    }
}

/**
 * @brief Заполнение массив с структурами изображений
 * 
 * @param partsOfImages - выходной массив с структурами изображений
 * @param images - входной map с файлами изображений
 */
void MultithreadedIntegral::fillingInPartsOfImages(std::vector<Image>& partsOfImages, const MapImages& images) const
{
    for (const auto& image : images) {
        for (uint8_t channel = 0; channel < image.second.size(); ++channel) {
            partsOfImages.push_back({ image.first, channel, image.second[channel] });
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

/**
 * @brief Ожидание завершения всех потоков
 * 
 */
void MultithreadedIntegral::waitingForEndOfThreads()
{
    for (auto& entry : _threads) {
        entry.join();
    }
}

// void MultithreadedIntegral::writeToFile(const std::vector<Image>& partsOfImages) const
// {
// }

/**
 * @brief Вычисление массива интегральных структур изображений
 * 
 * @param integralMatrices - массив выходных интегральных структур изображений
 * @param imagesMatrices -  массив входных структур изображений
 */
void MultithreadedIntegral::calculateIntegralImage(std::vector<Image>& integralMatrices, const std::vector<Image>& imagesMatrices)
{
    for (const auto& partOfImage : imagesMatrices) {
        if (isMatrixZeros(partOfImage.matrix)) {
            // Если матрица нулевая, то не вычисляем интеграл и просто пушим пустую матрицу
            cv::Mat empty;
            integralMatrices.push_back({ partOfImage.name, partOfImage.channel, empty });
        } else {
            cv::Mat integralMatrix;
            calculateIntegralMatrix(integralMatrix, partOfImage.matrix);
            integralMatrices.push_back({ partOfImage.name, partOfImage.channel, integralMatrix });
        }
    }
}

/**
 * @brief Проверка на нулевую матрицу
 * 
 * @param matrix - входная матрица
 * @return true - матрица нулевая
 * @return false - матрица не нулевая
 */
bool MultithreadedIntegral::isMatrixZeros(const cv::Mat& matrix)
{
    return !(cv::sum(cv::sum(matrix))[0] > 0);
}