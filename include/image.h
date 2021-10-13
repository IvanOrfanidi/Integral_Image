#pragma once

#include <opencv2/opencv.hpp>
#include <string>

using ThreeMatrixArray = std::array<cv::Mat, 3>;
using MapImages = std::map<std::string, ThreeMatrixArray>;

/**
 * @brief Условная структура одноканального изображения
 * 
 */
struct Image {
    std::string name; ///< Имя файла откуда была получена матрица
    unsigned channel; ///< Канал которому пренадлежала матрица
    cv::Mat matrix; ///< Одноканальная матрица
};

/**
 * @brief Вывод в поток условной структуры
 * 
 * @tparam StreamType - тип потока
 * @param stream - поток
 * @param image - условная структура
 * @return StreamType& - вывод
 */
template <class StreamType>
StreamType& operator<<(StreamType& stream, const Image& image)
{
    stream << "Name: " << image.name << std::endl
           << "Channel: " << image.channel << std::endl
           << "Matrix: " << std::endl
           << image.matrix << std::endl;
    return stream;
}