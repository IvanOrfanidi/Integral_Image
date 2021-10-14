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
 * @param partsOfIntegralImages - выходной массив структур одноканальных интегральных матриц с номером канала и именем файла
 * @param partsOfImages - входной массив структур одноканальных матриц с номером канала и именем файла
 */
void MultithreadedIntegral::calculate(std::vector<Image>& partsOfIntegralImages, const std::vector<Image>& partsOfImages)
{
    std::vector<std::vector<Image>> partsOfImagesForThreads;
    fillingPartsOfImagesForThreads(partsOfImagesForThreads, partsOfImages);

    std::vector<std::vector<Image>> partsOfIntegralImagesForThreads;
    giveDataToTasks(partsOfIntegralImagesForThreads, partsOfImagesForThreads);

    waitingForEndOfThreads();

    fillingPartsOfIntegralImages(partsOfIntegralImages, partsOfIntegralImagesForThreads);
}

/**
 * @brief Подготовка данных, заполнение массива одноканальный матриц
 * 
 * @param partsOfImagesForThreads выходной массив одноканальный матриц
 * @param partsOfImages - входной массив структур одноканальных матриц с номером канала и именем файла
 */
void MultithreadedIntegral::fillingPartsOfImagesForThreads(std::vector<std::vector<Image>>& partsOfImagesForThreads, const std::vector<Image>& partsOfImages) const
{
    partsOfImagesForThreads.resize(_numberOfThreads);
    unsigned countThreads = 0;
    for (const auto& partOfImage : partsOfImages) {
        partsOfImagesForThreads[countThreads].push_back(partOfImage);
        countThreads = (++countThreads >= _numberOfThreads) ? 0 : countThreads;
    }
}

/**
 * @brief Даем данные птокам и получаем выходной массив интегированных матриц
 * 
 * @param partsOfIntegralImagesFromThreads выходной массив интегированных одноканальный матриц
 * @param partsOfImagesForThreads входной массив одноканальный матриц
 */
void MultithreadedIntegral::giveDataToTasks(std::vector<std::vector<Image>>& partsOfIntegralImagesFromThreads, const std::vector<std::vector<Image>>& partsOfImagesForThreads)
{
    partsOfIntegralImagesFromThreads.resize(_numberOfThreads);
    _threads.resize(_numberOfThreads);
    for (unsigned countThreads = 0; countThreads < _numberOfThreads; ++countThreads) {
        const auto& imagesMatrices = partsOfImagesForThreads[countThreads];
        auto& integralMatrices = partsOfIntegralImagesFromThreads[countThreads];
        _threads[countThreads] = std::thread(calculateIntegralImage, std::ref(integralMatrices), std::ref(imagesMatrices));
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
 * @brief Выход данных, заполнение массива структур интегированных одноканальный матриц из массива интегированных одноканальный матриц
 * 
 * @param partsOfIntegralImages - выходной массив структур одноканальных интегральных матриц с номером канала и именем файла
 * @param partsOfIntegralImagesFromThreads - входной массив интегированных одноканальный матриц
 */
void MultithreadedIntegral::fillingPartsOfIntegralImages(std::vector<Image>& partsOfIntegralImages,
    const std::vector<std::vector<Image>>& partsOfIntegralImagesFromThreads) const
{
    partsOfIntegralImages.reserve(partsOfIntegralImagesFromThreads.size());
    for (const auto& partOfIntegralImageForThreads : partsOfIntegralImagesFromThreads) {
        std::copy(partOfIntegralImageForThreads.cbegin(), partOfIntegralImageForThreads.cend(), std::back_inserter(partsOfIntegralImages));
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