#include <integral.h>

/**
 * @brief Вычисление интегральной матрицы
 * 
 * @param dstMatrix - выходная интегральная матрица
 * @param srcMatrix - входная матрица
 */
void calculateIntegralMatrix(cv::Mat& dstMatrix, const cv::Mat& srcMatrix)
{
    dstMatrix = cv::Mat::zeros(srcMatrix.size(), CV_32FC1);
    for (int row = 0; row < srcMatrix.rows; row++) {
        for (int col = 0; col < srcMatrix.cols; col++) {
            if ((row == 0) && (col == 0)) {
                dstMatrix.at<float>(row, col) = srcMatrix.at<uint8_t>(row, col);
            } else if (row == 0 && col != 0) {
                dstMatrix.at<float>(row, col) = srcMatrix.at<uint8_t>(row, col) + dstMatrix.at<float>(row, col - 1);
            } else if (row != 0 && col == 0) {
                dstMatrix.at<float>(row, col) = srcMatrix.at<uint8_t>(row, col) + dstMatrix.at<float>(row - 1, col);
            } else {
                dstMatrix.at<float>(row, col) = srcMatrix.at<uint8_t>(row, col) + dstMatrix.at<float>(row - 1, col)
                    + dstMatrix.at<float>(row, col - 1) - dstMatrix.at<float>(row - 1, col - 1);
            }
        }
    }
}