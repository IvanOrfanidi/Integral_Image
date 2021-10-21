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
 * @details Результаты ожидаемых интегральных матриц теста взяты из функции cv::integral библиотеки OpenCV
 * 
 */
TEST(TestIntegral, Integral)
{
    // Arrange
    const std::vector<TestItem> testData = {
        {
            (cv::Mat_<uint8_t>(1, 3) << 3, 2, 1), ///< Test 1x3
            (cv::Mat_<float>(1, 3) << 3, 5, 6) ///< Expectation 1x3
        },
        {
            (cv::Mat_<uint8_t>(2, 2) << 1, 2, 3, 4), ///< Test 2x2
            (cv::Mat_<float>(2, 2) << 1, 3, 4, 10) ///< Expectation 3x2
        },
        {
            (cv::Mat_<uint8_t>(3, 2) << 0, 1, 2, 3, 4, 5), ///< Test 3x2
            (cv::Mat_<float>(3, 2) << 0, 1, 2, 6, 6, 15) ///< Expectation 3x2
        },
        {
            (cv::Mat_<uint8_t>(2, 3) << 0, 1, 2, 3, 4, 5), ///< Test 2x3
            (cv::Mat_<float>(2, 3) << 0, 1, 3, 3, 8, 15) ///< Expectation 2x3
        },
        {
            (cv::Mat_<uint8_t>(3, 3) << 0, 0, 0, 0, 0, 0, 0, 0, 0), ///< Test 3x3
            (cv::Mat_<float>(3, 3) << 0, 0, 0, 0, 0, 0, 0, 0, 0) ///< Expectation 3x3
        },
        {
            (cv::Mat_<uint8_t>(3, 3) << 255, 254, 253, 252, 251, 250, 127, 128, 129), ///< Test 3x3
            (cv::Mat_<float>(3, 3) << 255, 509, 762, 507, 1012, 1515, 634, 1267, 1899) ///< Expectation 3x3
        },
        {
            (cv::Mat_<uint8_t>(3, 3) << 255, 255, 255, 255, 255, 255, 255, 255, 255), ///< Test 3x3
            (cv::Mat_<float>(3, 3) << 255, 510, 765, 510, 1020, 1530, 765, 1530, 2295) ///< Expectation 3x3
        },

    };
    cv::Mat resMatrix;

    for (const auto& testItem : testData) {
        // Act
        calculateIntegralMatrix(testItem.testMatrix, resMatrix);

        // Assert
        EXPECT_TRUE(utils::isMatMatches(resMatrix, testItem.expectedMatrix)) << "Test Matrix:" << std::endl
                                                                             << testItem.testMatrix << std::endl
                                                                             << "Expected Matrix:" << std::endl
                                                                             << testItem.expectedMatrix;
    }
}