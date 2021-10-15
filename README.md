### Настройка среды

+ Если cборка для Ubuntu, то рекомендуется использовать сборку через Docker и настройка среды сводится к установке только Docker
(https://docs.docker.com/engine/install/).

+ Установить компилятор **GCC** или **LLVM** и установить систему сборки **CMake**
согласно рекомендациям данной ОС и версии компилятора, для GCC не ниже 8.2 и CMake не ниже 3.16.

+ Чтобы программа собралась под Widows7/10 и Linux (Ubuntu 18/20) необходимо отдельно
поставить библиотеки **boost** и **OpenCV** согласно рекомендациям данной ОС.
Так для Windows хорошим решением будет платформа **MSYS2** (https://www.msys2.org/).
Для Ubuntu все библиотеки можно поставить из менеджера **apt**.
* `sudo apt-get install libboost-dev libboost-all-dev`
* `sudo apt-get install libopencv-dev`

+ Альтернативный вариант установки библиотек из менеджера пакетов Conan.

### Сборка для Ubuntu через Docker(рекомендуемый способ).
+ Выполнить скрипт `install_from_docker.sh`.
```sh
docker build -t integral-image:latest .
docker create -it --name dummy integral-image:latest
rm -rf build && mkdir build && cd build/
docker cp dummy:/Integral_Image/build/integral_image .
docker cp dummy:/Integral_Image/build/bin .
docker rm -f dummy
```
+ Исполняемый файл и тесты будут лежать в папке `build`.

### Сборка через CMake.
+ Выполнить команду в папке со сборкой(build, out):
* `cmake -G "Unix Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release ..`
* `cmake --build .`


### Сборка тестов с Google Test через CMake.

#### Установка менеджера пакетов Conan через pip.
* `pip install conan`

+ Выполнить команду в папке со сборкой(build, out):
* `conan install ../ -s build_type=Debug`.
В случае ошибки необходимо подправить профиль для conan `.conan/profiles/default`:
```sh
[settings]
os=Linux
os_build=Linux
arch=x86_64
arch_build=x86_64
compiler=gcc
compiler.version=8
compiler.libcxx=libstdc++11
build_type=Release
[options]
[build_requires]
[env]
```
В профиле для conan нужно подправить компилятор `compiler=gcc`, его версию `compiler.version=8` и версию C++ `compiler.libcxx=libstdc++11`.

#### Сборка тестов через CMake.
+ Выполнить команду в папке со сборкой(build, out):
* `cmake cmake -G "Unix Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DTESTS=true ..`
* `cmake --build .`

+ Тесты будут лежать в папке `bin`.