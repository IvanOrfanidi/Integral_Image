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
    /**
     * @brief Конструктор класса MultithreadedIntegral
     * 
     * @param numberOfThreads - количество потоков
     */
    explicit MultithreadedIntegral(unsigned numberOfThreads) noexcept;

    /**
     * @brief Вычисление интегральных матриц
     * 
     * @param partsOfIntegralImages - массив структур одноканальных интегральных матриц с номером канала и именем файла
     * @param partsOfImages - массив структур одноканальных матриц с номером канала и именем файла
     */
    void calculate(std::vector<Image>& partsOfIntegralImages, const std::vector<Image>& partsOfImages);

private:
    /**
     * @brief Ожидание завершения всех потоков
     * 
     */
    void waitingForEndOfThreads();

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