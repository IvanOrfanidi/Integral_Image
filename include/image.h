#pragma once

#include <opencv2/opencv.hpp>
#include <string>

struct Image {
    std::string name;
    unsigned channel;
    cv::Mat matrix;
};

template <class StreamType>
StreamType& operator<<(StreamType& stream, const Image& image)
{
    stream << "Name: " << image.name
           << "\nChannel: " << image.channel
           << "\nMatrix: \n"
           << image.matrix << '\n';
    return stream;
}