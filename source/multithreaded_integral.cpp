#include <multithreaded_integral.h>
#include <utils.h>

#include <array>

#include <opencv2/core.hpp>

/**
 * @brief Конструктор класса MultithreadedIntegral
 * 
 * @param numberOfThreads - количество потоков
 */
MultithreadedIntegral::MultithreadedIntegral(unsigned numberOfThreads) noexcept
    : _numberOfThreads(numberOfThreads)
{
}

/**
 * @brief Вычисление интегральных матриц
 * 
 * @param partsOfIntegralImages - массив структур одноканальных интегральных матриц с номером канала и именем файла
 * @param partsOfImages - массив структур одноканальных матриц с номером канала и именем файла
 */
void MultithreadedIntegral::calculate(std::vector<Image>& partsOfIntegralImages, const std::vector<Image>& partsOfImages)
{
    unsigned countThreads = 0;
    std::vector<std::vector<Image>> partsOfImagesForThreads(_numberOfThreads);
    for (const auto& partOfImage : partsOfImages) {
        partsOfImagesForThreads[countThreads].push_back(partOfImage);
        countThreads = (++countThreads >= _numberOfThreads) ? 0 : countThreads;
    }

    std::vector<std::vector<Image>> partsOfIntegralImagesForThreads(_numberOfThreads);
    _threads.resize(_numberOfThreads);
    for (countThreads = 0; countThreads < _numberOfThreads; ++countThreads) {
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

/**
 * @brief Вычисление массива интегральных структур изображений
 * 
 * @param integralMatrices - массив выходных интегральных структур изображений
 * @param imagesMatrices -  массив входных структур изображений
 */
void MultithreadedIntegral::calculateIntegralImage(std::vector<Image>& integralMatrices, const std::vector<Image>& imagesMatrices)
{
    for (const auto& partOfImage : imagesMatrices) {
        if (utils::isMatrixZeros(partOfImage.matrix)) {
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