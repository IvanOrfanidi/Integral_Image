#pragma once

#include <opencv2/opencv.hpp>

/**
 * @brief Вычисление интегральной матрицы
 * 
 * @param srcMatrix - входная матрица
 * @param dstMatrix - выходная интегральная матрица
 */
void calculateIntegralMatrix(const cv::Mat& srcMatrix, cv::Mat& dstMatrix);