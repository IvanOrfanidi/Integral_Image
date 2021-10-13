#pragma once

#include <thread>

#include <config.h>
#include <image.h>
#include <integral.h>

/**
 * @brief Класс вычисления интегральных изображений в многопоточке
 * 
 */
class MultithreadedIntegral {
public:
    explicit MultithreadedIntegral(unsigned numberOfThreads) noexcept;

    void calculate(std::vector<Image>& partsOfIntegralImages, const std::vector<Image>& partsOfImages);

private:
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

    unsigned _numberOfThreads; ///< Кол-во потоков
    std::vector<std::thread> _threads; ///< Вектор потоков
};