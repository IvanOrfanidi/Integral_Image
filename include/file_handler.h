#pragma once

#include <config.h>
#include <image.h>

class FileHandler {
public:
    FileHandler(const std::set<std::string> pathsToImages);

    /**
     * @brief Чтение файлов
     * 
     * @param partsOfImages - массив структуры одноканальных матриц с номером канала и именем файла
     */
    void read(std::vector<Image>& partsOfImages) const;

    void write(const std::vector<Image>& partsOfIntegralImages) const;

private:
    /**
     * @brief Заполнение массив с структурами изображений
     * 
     * @param partsOfImages - выходной массив с структурами изображений
     * @param images - входной map с файлами изображений
     */
    void fillingInPartsOfImages(std::vector<Image>& partsOfImages, const MapImages& threeChannelMatrices) const;

    std::set<std::string> _pathsToImages; ///< Перечисление файлов
};
