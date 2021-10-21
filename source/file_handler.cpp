#include <file_handler.h>
#include <message.h>

#include <fstream>

/**
 * @brief Конструктор класса работающего с файлами
 * 
 * @param pathsToImages - перечисление файлов
 */
FileHandler::FileHandler(const std::set<std::string> pathsToImages)
    : _pathsToImages(std::move(pathsToImages))
{
}

/**
 * @brief Чтение файлов
 * 
 * @param partsOfImages - массив структуры одноканальных матриц с номером канала и именем файла
 */
void FileHandler::dataRead(std::vector<Image>& partsOfImages) const
{
    MapImages inputData; // Список изображений(3-х канальных матриц) с именем файла
    for (const auto& pathToImage : _pathsToImages) {
        cv::Mat image = cv::imread(pathToImage);
        if (image.empty()) {
            ERR_INFO("couldn't open or find image file: " + pathToImage);
            continue;
        }

        ThreeMatrixArray channels; // BGR
        cv::split(image, channels);
        inputData.insert({ pathToImage, std::move(channels) });
    }

    DEB_INFO("INPUT DATA:");
    for (const auto& data __attribute__((unused)) : inputData) {
        DEB_INFO("File name: " << data.first);
        for (size_t i = 0; i < data.second.size(); ++i) {
            DEB_INFO("Channel: " << i);
            DEB_INFO("Matrix: " << std::endl
                                << data.second[i]);
        }
    }
    DEB_INFO(std::endl);

    fillingInPartsOfImages(inputData, partsOfImages);
}

/**
 * @brief Заполнение массив с структурами изображений
 * 
 * @param images - входной map с файлами изображений
 * @param partsOfImages - выходной массив с структурами изображений
 */
void FileHandler::fillingInPartsOfImages(const MapImages& images, std::vector<Image>& partsOfImages) const
{
    for (const auto& image : images) {
        for (unsigned channel = 0; channel < image.second.size(); ++channel) {
            partsOfImages.push_back({ image.first, channel, image.second[channel] });
        }
    }
}

/**
 * @brief Пишем данные в выходной файл
 * 
 * @param partsOfIntegralImages - массив структур одноканальных интегральных матриц с номером канала и именем файла
 */
void FileHandler::dataWrite(const std::vector<Image>& partsOfIntegralImages) const
{
    for (const auto& pathToImage : _pathsToImages) {
        std::map<unsigned, cv::Mat> outputData;
        for (const auto& partOfIntegralImage : partsOfIntegralImages) {
            if (pathToImage == partOfIntegralImage.name) {
                outputData.insert({ partOfIntegralImage.channel, partOfIntegralImage.matrix });
            }
        }

        DEB_INFO("OUTPUT DATA:");
        for (const auto& data __attribute__((unused)) : outputData) {
            DEB_INFO("Channel: " << data.first);
            DEB_INFO("Matrix: " << std::endl
                                << data.second);
        }
        DEB_INFO(std::endl);

        const std::string fileName = getFileNameFromPath(pathToImage);
        writeToFile(fileName, outputData);
    }
}

/**
 * @brief Получение имени выходного файла из пути к нему
 * 
 * @param path - путь к файлу
 * @return std::string - имя файла
 */
std::string FileHandler::getFileNameFromPath(const std::string& path) const
{
    const std::string baseFilename = path.substr(path.find_last_of("/\\") + 1);
    std::string::size_type const pos(baseFilename.find_last_of('.'));
    std::string fileName = baseFilename.substr(0, pos);
    return fileName + EXTENSION.data();
}

/**
 * @brief Запись интегральных матриц в выходной файл
 * 
 * @param nameFile - имя выходного файла
 * @param outputData - упорядоченный список интегральных матриц
 */
void FileHandler::writeToFile(const std::string& nameFile, const std::map<unsigned, cv::Mat>& outputData) const
{
    std::ofstream file(nameFile);
    if (file.is_open()) {
        for (const auto& data : outputData) {
            const cv::Mat& matrix = data.second;
            if (matrix.empty()) {
                file << std::endl;
            } else {
                for (int row = 0; row < matrix.rows; ++row) {
                    for (int col = 0; col < matrix.cols; ++col) {
                        const float value = matrix.at<float>(row, col);
                        // Согласно требованию выводим значение до одного знака после запятой
                        file << " " << std::setprecision(1) << std::fixed << value;
                    }
                    file << std::endl;
                }
            }
            file << std::endl;
        }
        file.close();
    }
}