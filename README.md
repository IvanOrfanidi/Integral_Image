### Сборка.
+ Программа собирается под Widows7/10 и Linux (Ubuntu 18/20)

#### Сборка через CMake.
+ Выполнить команду в папке со сборкой(build, out):
* `cmake -G "Unix Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release ..`
* `cmake --build .`

### Сборка тестов с Google Test.

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

  + Для последующих вызовов:
* `conan install ../ -s build_type=Debug`

#### Сборка тестов через CMake.
+ Выполнить команду в папке со сборкой(build, out):
* `cmake cmake -G "Unix Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DTEST=true ..`
* `cmake --build .`

+ Тесты будут лежать в папке `bin`.