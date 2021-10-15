# Get image from Docker Hub
FROM iorfanidi/ubuntu-20.04-gcc-cmake-git-python3-pip-conan:latest

# Specify the working directory
WORKDIR /Integral_Image

# Copy the current folder which contains C++ source code to the Docker image
COPY . /Integral_Image

# Update apps on the base image
RUN apt-get update && \
    apt-get install -y \
    libboost-dev \
    libboost-all-dev \
    libopencv-dev && \
    # Build
    rm -rf build && mkdir build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release .. && \
    cmake --build . && \
    # Conan install
    ls | grep -v integral_image | xargs rm -rfv && \
    conan install ../ -s build_type=Debug && \
    # Tests build
    cmake -DCMAKE_BUILD_TYPE=Release -DTESTS=true .. && \
    cmake --build .