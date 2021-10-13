#include <utils.h>

namespace utils {
/**
 * @brief Сравнение двух матриц в "лоб"(без дельты для float и double)
 * 
 * @param firstMatrix - первая матрица
 * @param secondMatrix - вторая матрица
 * @return true - матрицы равны
 * @return false - матрицы не равны
 */
bool isMatMatches(const cv::Mat& firstMatrix, const cv::Mat& secondMatrix)
{
    if (firstMatrix.dims == secondMatrix.dims && firstMatrix.size == secondMatrix.size && firstMatrix.elemSize() == secondMatrix.elemSize()) {
        if (firstMatrix.isContinuous() && secondMatrix.isContinuous()) {
            return 0 == memcmp(firstMatrix.ptr(), secondMatrix.ptr(), firstMatrix.total() * firstMatrix.elemSize());
        } else {
            const cv::Mat* arrays[] = { &firstMatrix, &secondMatrix, 0 };
            uint8_t* ptrs[2];
            cv::NAryMatIterator it(arrays, ptrs, 2);
            for (unsigned int p = 0; p < it.nplanes; p++, ++it) {
                if (0 != memcmp(it.ptrs[0], it.ptrs[1], it.size * firstMatrix.elemSize())) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

/**
 * @brief Проверка на нулевую матрицу
 * 
 * @param matrix - входная матрица
 * @return true - матрица нулевая
 * @return false - матрица не нулевая
 */
bool isMatrixZeros(const cv::Mat& matrix)
{
    return !(cv::sum(cv::sum(matrix))[0] > 0);
}
}