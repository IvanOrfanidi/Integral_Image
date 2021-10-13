## Сборка тестов с Google Test.

### Установка менеджера pip и менеджера пакетов Conan.
`sudo apt install pip`
`pip install conan`
`sudo reboot`

+ Выполнить команду в папке со сборкой(build, out):
  + Для первого вызова:
`conan install ../ -s build_type=Debug`. В случае ошибки необходимо подправить профиль для conan `.conan/profiles/default`:
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
`conan install ../ -s build_type=Debug`
