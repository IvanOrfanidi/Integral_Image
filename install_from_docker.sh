#!/bin/bash

docker build -t integral-image:latest .
docker create -it --name dummy integral-image:latest
rm -rf build && mkdir build && cd build/
docker cp dummy:/Integral_Image/build/integral_image .
docker cp dummy:/Integral_Image/build/bin .
docker rm -f dummy