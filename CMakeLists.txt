# Version CMake
cmake_minimum_required(VERSION 3.16)

# Project name
project(integral_image)

# Include lib conan test
if(TEST)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endif()

# Options
set(CMAKE_CXX_STANDARD 17)

# Compiler-specific options
if((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    add_compile_options(
        -Werror
        -Wall
        -Wextra
        -Wpedantic
        -Wcast-align
        -Wcast-qual
        -Wenum-compare
        -Wfloat-equal
        -Wnon-virtual-dtor
        -Woverloaded-virtual
        -Wredundant-decls
    )
endif()

# Source files
file(GLOB_RECURSE SOURCES
    source/*.cpp
)

# Source tests files
file(GLOB_RECURSE TEST_SOURCES
    test/*.cpp
)

# Boost components
set(BOOST_COMPONENTS
    program_options
    system
    filesystem
)
find_package(Boost COMPONENTS ${BOOST_COMPONENTS} REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Threads)

# Include directories
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    stdc++fs
    ${OpenCV_LIBS}
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)

if(TEST)
    add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})

    target_link_libraries(${PROJECT_NAME}_tests
    ${OpenCV_LIBS}
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ${CONAN_LIBS})
endif()