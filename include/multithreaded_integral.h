#pragma once

#include <thread>

#include <config.h>
#include <image.h>
#include <integral.h>

using MapThreeChannelMatrices = std::map<std::string, std::array<cv::Mat, 3>>;

class MultithreadedIntegral {
public:
    explicit MultithreadedIntegral(Config config) noexcept;

    void execute();

private:
    static void calculateIntegralImage(std::vector<Image>& integralMatrices, const std::vector<Image>& imagesMatrices);

    void fillingInThreeChannelMatrices(MapThreeChannelMatrices& threeChannelMatrices) const;

    void fillingInQueueMatrices(std::vector<Image>& partsOfImages, const MapThreeChannelMatrices& threeChannelMatrices) const;

    void calculate(std::vector<Image>& partsOfIntegralImages, const std::vector<Image>& partsOfImages);

    void waitingForEndOfThreads();

    Config _config;
    std::vector<std::thread> _threads;
};