#pragma once

#include <opencv2/opencv.hpp>

/**
 * @brief Вычисление интегральной матрицы
 * 
 * @param dstMatrix - выходная интегральная матрица
 * @param srcMatrix - входная матрица
 */
void calculateIntegralMatrix(cv::Mat& dstMatrix, const cv::Mat& srcMatrix);