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

/**
 * @brief Проверка на нулевую матрицу
 * 
 * @param matrix - входная матрица
 * @return true - матрица нулевая
 * @return false - матрица не нулевая
 */
bool isMatrixZeros(const cv::Mat& matrix);
}