#pragma once

#include <opencv2/opencv.hpp>

namespace utils {
/**
 * @brief Сравнение двух матриц в "лоб"(без дельты для float и double)
 * 
 * @param firstMatrix - первая матрица
 * @param secondMatrix - вторая матрица
 * @return true - матрицы равны
 * @return false - матрицы не равны
 */
bool isMatMatches(const cv::Mat& Mat1, const cv::Mat& Mat2);
}