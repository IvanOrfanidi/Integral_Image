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
     * @param partsOfImages - входной массив структур одноканальных матриц с номером канала и именем файла
     * @param partsOfIntegralImages - выходной массив структур одноканальных интегральных матриц с номером канала и именем файла
     */
    void calculate(const std::vector<Image>& partsOfImages, std::vector<Image>& partsOfIntegralImages);

private:
    /**
     * @brief Подготовка данных, заполнение массива одноканальный матриц
     * 
     * @param partsOfImages - входной массив структур одноканальных матриц с номером канала и именем файла
     * @param partsOfImagesForThreads - выходной массив одноканальный матриц
     */
    void fillingPartsOfImagesForThreads(const std::vector<Image>& partsOfImages, std::vector<std::vector<Image>>& partsOfImagesForThreads) const;

    /**
     * @brief Даем данные птокам и получаем выходной список интегированных матриц
     * 
     * @param partsOfImagesForThreads - входной список одноканальный матриц
     * @param partsOfIntegralImagesFromThreads - выходной список интегированных одноканальный матриц
     */
    void giveDataToTasks(const std::vector<std::vector<Image>>& partsOfImagesForThreads, std::vector<std::vector<Image>>& partsOfIntegralImagesFromThreads);

    /**
     * @brief Ожидание завершения всех потоков
     * 
     */
    void waitingForEndOfThreads();

    /**
     * @brief Выход данных, заполнение массива структур интегированных одноканальный матриц из массива интегированных одноканальный матриц
     * 
     * @param partsOfIntegralImagesFromThreads - входной массив интегированных одноканальный матриц
     * @param partsOfIntegralImages - выходной массив структур одноканальных интегральных матриц с номером канала и именем файла
     */
    void fillingPartsOfIntegralImages(const std::vector<std::vector<Image>>& partsOfIntegralImagesFromThreads, std::vector<Image>& partsOfIntegralImages) const;

    /**
     * @brief Вычисление массива интегральных структур изображений
     * 
     * @param imagesMatrices - массив входных структур изображений
     * @param integralMatrices - массив выходных интегральных структур изображений
     */
    static void calculateIntegralImage(const std::vector<Image>& imagesMatrices, std::vector<Image>& integralMatrices);

    unsigned _numberOfThreads; ///< Кол-во потоков
    std::vector<std::thread> _threads; ///< Вектор потоков
};