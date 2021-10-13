#include <gtest/gtest.h>
#include <utils.h>

/**
 * @brief Структура тестовых данных
 * 
 */
struct TestItem {
    cv::Mat testMatrix; ///< Тестовая матрица
    cv::Mat matchesMatrix; ///< Матрица равная тестовой
    cv::Mat mismatchesMatrix; ///< Матрица неравная тестовой
};

/**
 * @brief Тест функции сравнения матриц
 * 
 * @tparam T - типы для тестирования (MatMatchesTypesT)
 */
template <class T>
class FXMatMatches : public ::testing::TestWithParam<T> {
};

TYPED_TEST_CASE_P(FXMatMatches);
TYPED_TEST_P(FXMatMatches, MatMatches)
{
    // Arrange
    TypeParam test;

    for (const auto& testItem : test.data) {
        // Act
        const bool isMatches = utils::isMatMatches(testItem.testMatrix, testItem.matchesMatrix);
        const bool isMismatches = utils::isMatMatches(testItem.testMatrix, testItem.mismatchesMatrix);

        // Assert
        EXPECT_TRUE(isMatches) << "Test Matrix:" << std::endl
                               << testItem.testMatrix << std::endl
                               << "Matches Matrix:" << std::endl
                               << testItem.matchesMatrix;
        EXPECT_FALSE(isMismatches) << "Test Matrix:" << std::endl
                                   << testItem.testMatrix << std::endl
                                   << "Mismatches Matrix:" << std::endl
                                   << testItem.mismatchesMatrix;
    }
}
REGISTER_TYPED_TEST_CASE_P(FXMatMatches, MatMatches);

/**
 * @brief Перечисление тестовых данных
 * 
 * @tparam T тип U8
 */
template <class T>
struct U8TestItem {
    const std::vector<TestItem> data = {
        {
            (cv::Mat_<T>(1, 1) << 121), ///< Test 1x1
            (cv::Mat_<T>(1, 1) << 121), ///< Matches 1x1
            (cv::Mat_<T>(1, 1) << 212) ///< Mismatches 1x1
        },
        {
            (cv::Mat_<T>(1, 2) << 255, 0), ///< Test 1x2
            (cv::Mat_<T>(1, 2) << 255, 0), ///< Matches 1x2
            (cv::Mat_<T>(1, 2) << 0, 255) ///< Mismatches 1x2
        },
        {
            (cv::Mat_<T>(2, 2) << 4, 3, 2, 1), ///< Test 2x2
            (cv::Mat_<T>(2, 2) << 4, 3, 2, 1), ///< Matches 2x2
            (cv::Mat_<T>(2, 2) << 4, 0, 2, 1) ///< Mismatches 2x2
        },
        {
            (cv::Mat_<T>(2, 3) << 0, 1, 2, 3, 4, 5), ///< Test 2x3
            (cv::Mat_<T>(2, 3) << 0, 1, 2, 3, 4, 5), ///< Matches 2x3
            (cv::Mat_<T>(2, 3) << 0, 1, 2, 3, 255, 5) ///< Mismatches 2x3
        },
        {
            (cv::Mat_<T>(3, 3) << 255, 254, 253, 252, 251, 250, 127, 128, 129), ///< Test 3x3
            (cv::Mat_<T>(3, 3) << 255, 254, 253, 252, 251, 250, 127, 128, 129), ///< Matches 3x3
            (cv::Mat_<T>(3, 3) << 255, 254, 253, 252, 251, 250, 0, 128, 129) ///< Mismatches 3x3
        },
    };
};

/**
 * @brief Перечисление тестовых данных
 * 
 * @tparam T тип float
 */
template <class T>
struct FloatTestItem {
    const std::vector<TestItem> data = {
        {
            (cv::Mat_<T>(1, 1) << 1.234), ///< Test 1x1
            (cv::Mat_<T>(1, 1) << 1.234), ///< Matches 1x1
            (cv::Mat_<T>(1, 1) << -1.234) ///< Mismatches 1x1
        },
        {
            (cv::Mat_<T>(1, 2) << -1.234, 9.876), ///< Test 1x2
            (cv::Mat_<T>(1, 2) << -1.234, 9.876), ///< Matches 1x2
            (cv::Mat_<T>(1, 2) << -1.235, 9.8761) ///< Mismatches 1x2
        },
        {
            (cv::Mat_<T>(2, 2) << 1.1, 2.2, 3.3, 4.4), ///< Test 2x2
            (cv::Mat_<T>(2, 2) << 1.1, 2.2, 3.3, 4.4), ///< Matches 2x2
            (cv::Mat_<T>(2, 2) << 1.1, 2.22, 3.3, 4.4) ///< Mismatches 2x2
        },
        {
            (cv::Mat_<T>(2, 3) << 1000.0001, 2000.0002, 3000.0003, 4000.0004, 5000.0005, 6000.0006), ///< Test 2x3
            (cv::Mat_<T>(2, 3) << 1000.0001, 2000.0002, 3000.0003, 4000.0004, 5000.0005, 6000.0006), ///< Matches 2x3
            (cv::Mat_<T>(2, 3) << -1000.0001, 2000.0002, 3000.0003, 4000.0004, 5000.0005, 6000.0006) ///< Mismatches 2x3
        },
        {
            (cv::Mat_<T>(3, 3) << 9000.0009, -8000.0008, 7000.0007, -6000.0006, 5000.0005, -4000.0004, 3000.0003, -2000.0002, 1000.0001), ///< Test 3x3
            (cv::Mat_<T>(3, 3) << 9000.0009, -8000.0008, 7000.0007, -6000.0006, 5000.0005, -4000.0004, 3000.0003, -2000.0002, 1000.0001), ///< Matches 3x3
            (cv::Mat_<T>(3, 3) << 9000.0009, -8000.0008, 7000.0007, -6000.0006, 5000.0005, -4000.0014, 3000.0003, -2000.0002, 1000.0001) ///< Mismatches 3x3
        }
    };
};

/**
 * @brief Типы для тестирования
 * 
 */
typedef ::testing::Types<
    U8TestItem<uint8_t>,
    FloatTestItem<float>>
    MatMatchesTypesT;
INSTANTIATE_TYPED_TEST_CASE_P(MatMatches, FXMatMatches, MatMatchesTypesT);