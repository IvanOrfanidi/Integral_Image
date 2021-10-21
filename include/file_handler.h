#pragma once

#include <config.h>
#include <image.h>

class FileHandler {
public:
    /**
     * @brief Конструктор класса работающего с файлами
     * 
     * @param pathsToImages - перечисление файлов
     */
    explicit FileHandler(const std::set<std::string> pathsToImages);

    /**
     * @brief Чтение файлов
     * 
     * @param partsOfImages - массив структуры одноканальных матриц с номером канала и именем файла
     */
    void dataRead(std::vector<Image>& partsOfImages) const;

    /**
     * @brief Пишем данные в выходной файл
     * 
     * @param partsOfIntegralImages - массив структур одноканальных интегральных матриц с номером канала и именем файла
     */
    void dataWrite(const std::vector<Image>& partsOfIntegralImages) const;

private:
    static constexpr std::string_view EXTENSION = ".integral"; ///< Заданное расширение выходных файлов

    /**
     * @brief Заполнение массив с структурами изображений
     * 
     * @param images - входной map с файлами изображений
     * @param partsOfImages - выходной массив с структурами изображений
     */
    void fillingInPartsOfImages(const MapImages& threeChannelMatrices, std::vector<Image>& partsOfImages) const;

    /**
     * @brief Получение имени выходного файла из пути к нему
     * 
     * @param path - путь к файлу
     * @return std::string - имя файла
     */
    std::string getFileNameFromPath(const std::string& path) const;

    /**
     * @brief Запись интегральных матриц в выходной файл
     * 
     * @param nameFile - имя выходного файла
     * @param outputData - упорядоченный список интегральных матриц
     */
    void writeToFile(const std::string& fileName, const std::map<unsigned, cv::Mat>& outputData) const;

    std::set<std::string> _pathsToImages; ///< Перечисление файлов
};
