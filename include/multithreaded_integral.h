#pragma once

#include <thread>

#include <config.h>
#include <image.h>
#include <integral.h>

using ThreeMatrixArray = std::array<cv::Mat, 3>;
using MapImages = std::map<std::string, ThreeMatrixArray>;

/**
 * @brief Класс вычисления интегральных изображений в многопоточке
 * 
 */
class MultithreadedIntegral {
public:
    explicit MultithreadedIntegral(Config config) noexcept;

    void execute();

private:
    /**
     * @brief Заполнение мепа файлами изображений
     * 
     * @param images - входной map с файлами изображений
     */
    void fillingInImages(MapImages& threeChannelMatrices) const;

    void fillingInPartsOfImages(std::vector<Image>& partsOfImages, const MapImages& threeChannelMatrices) const;

    void calculate(std::vector<Image>& partsOfIntegralImages, const std::vector<Image>& partsOfImages);

    /**
     * @brief Ожидание завершения всех потоков
     * 
     */
    void waitingForEndOfThreads();

    void writeToFile(const std::vector<Image>& partsOfImages) const;

    /**
     * @brief Вычисление массива интегральных структур изображений
     * 
     * @param integralMatrices - массив выходных интегральных структур изображений
     * @param imagesMatrices -  массив входных структур изображений
     */
    static void calculateIntegralImage(std::vector<Image>& integralMatrices, const std::vector<Image>& imagesMatrices);

    /**
     * @brief Проверка на нулевую матрицу
     * 
     * @param matrix - входная матрица
     * @return true - матрица нулевая
     * @return false - матрица не нулевая
     */
    static bool isMatrixZeros(const cv::Mat& matrix);

    Config _config; ///< Конфигурация
    std::vector<std::thread> _threads; ///< Вектор потоков
};