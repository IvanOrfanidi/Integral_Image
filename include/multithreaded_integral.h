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
     * @param partsOfIntegralImages - выходной массив структур одноканальных интегральных матриц с номером канала и именем файла
     * @param partsOfImages - входной массив структур одноканальных матриц с номером канала и именем файла
     */
    void calculate(std::vector<Image>& partsOfIntegralImages, const std::vector<Image>& partsOfImages);

private:
    /**
     * @brief Подготовка данных, заполнение массива одноканальный матриц
     * 
     * @param partsOfImagesForThreads выходной массив одноканальный матриц
     * @param partsOfImages - входной массив структур одноканальных матриц с номером канала и именем файла
     */
    void fillingPartsOfImagesForThreads(std::vector<std::vector<Image>>& partsOfImagesForThreads, const std::vector<Image>& partsOfImages) const;

    /**
     * @brief Даем данные птокам и получаем выходной список интегированных матриц
     * 
     * @param partsOfIntegralImagesFromThreads выходной список интегированных одноканальный матриц
     * @param partsOfImagesForThreads входной список одноканальный матриц
     */
    void giveDataToTasks(std::vector<std::vector<Image>>& partsOfIntegralImagesFromThreads, const std::vector<std::vector<Image>>& partsOfImagesForThreads);

    /**
     * @brief Ожидание завершения всех потоков
     * 
     */
    void waitingForEndOfThreads();

    /**
     * @brief Выход данных, заполнение массива структур интегированных одноканальный матриц из массива интегированных одноканальный матриц
     * 
     * @param partsOfIntegralImages - выходной массив структур одноканальных интегральных матриц с номером канала и именем файла
     * @param partsOfIntegralImagesFromThreads - входной массив интегированных одноканальный матриц
     */
    void fillingPartsOfIntegralImages(std::vector<Image>& partsOfIntegralImages, const std::vector<std::vector<Image>>& partsOfIntegralImagesFromThreads) const;

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