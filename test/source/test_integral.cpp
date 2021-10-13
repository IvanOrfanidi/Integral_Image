#include <gtest/gtest.h>
#include <integral.h>
#include <utils.h>

/**
 * @brief Структура тестовых данных
 * 
 */
struct TestItem {
    cv::Mat testMatrix; ///< Тестовая матрица
    cv::Mat expectedMatrix; ///< Ожидаемая матрица
};

/**
 * @brief Тест функции получения интегральной матрицы
 * 
 */
TEST(TestIntegral, Integral)
{
    // Arrange
    const std::vector<TestItem> testData = {
        {
            (cv::Mat_<uint8_t>(3, 2) << 0, 1, 2, 3, 4, 5), ///< Test 3x2
            (cv::Mat_<float>(3, 2) << 0, 1, 2, 6, 6, 15), ///< Expectation 3x2
        }
    };
    cv::Mat resMatrix;

    for (const auto& testItem : testData) {
        // Act
        calculateIntegralMatrix(resMatrix, testItem.testMatrix);

        // Assert
        EXPECT_TRUE(utils::isMatMatches(resMatrix, testItem.expectedMatrix));
    }
}