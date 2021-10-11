#include <integral.h>

cv::Mat integral(const cv::Mat& srcMatrix)
{
    cv::Mat resMatrix = cv::Mat::zeros(srcMatrix.size(), CV_32FC1);
    for (int row = 0; row < srcMatrix.rows; row++) {
        for (int col = 0; col < srcMatrix.cols; col++) {
            if ((row == 0) && (col == 0)) {
                resMatrix.at<float>(row, col) = srcMatrix.at<uint8_t>(row, col);
            } else if (row == 0 && col != 0) {
                resMatrix.at<float>(row, col) = srcMatrix.at<uint8_t>(row, col) + resMatrix.at<float>(row, col - 1);
            } else if (row != 0 && col == 0) {
                resMatrix.at<float>(row, col) = srcMatrix.at<uint8_t>(row, col) + resMatrix.at<float>(row - 1, col);
            } else {
                resMatrix.at<float>(row, col) = srcMatrix.at<uint8_t>(row, col) + resMatrix.at<float>(row - 1, col)
                    + resMatrix.at<float>(row, col - 1) - resMatrix.at<float>(row - 1, col - 1);
            }
        }
    }

    return resMatrix;
}