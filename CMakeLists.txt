# Version CMake
cmake_minimum_required(VERSION 3.16)

# Project
project(integral_image
    VERSION 1.0.0
)

configure_file(
    project_version.h.in ${CMAKE_CURRENT_BINARY_DIR}/project_version.h
)

# All tests
if(TEST)
    set(MAT_MATCHES_TEST ON)
    set(MAT_INTEGRAL_TEST ON)
endif()

# Include lib conan test
if(MAT_MATCHES_TEST OR MAT_INTEGRAL_TEST)
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
file(GLOB_RECURSE MAT_MATCHES_TEST_SOURCES
    test/test_mat_matches.cpp
    source/utils.cpp
)
file(GLOB_RECURSE MAT_INTEGRAL_TEST_SOURCES
    test/test_integral.cpp
    source/utils.cpp
    source/integral.cpp
)

# Boost components
set(BOOST_COMPONENTS
    program_options
    system
)
find_package(Boost COMPONENTS ${BOOST_COMPONENTS} REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Threads)

# Include directories
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Executable project
if(NOT TEST)
    add_executable(${PROJECT_NAME} ${SOURCES})
    target_link_libraries(${PROJECT_NAME}
        ${OpenCV_LIBS}
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
    )
    target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
    )
endif()

# Executable tests
if(MAT_MATCHES_TEST)
    add_executable(mat_matches_test ${MAT_MATCHES_TEST_SOURCES})
    target_link_libraries(mat_matches_test
    ${OpenCV_LIBS}
    ${CONAN_LIBS})
endif()
if(MAT_INTEGRAL_TEST)
    add_executable(mat_integral_test ${MAT_INTEGRAL_TEST_SOURCES})
    target_link_libraries(mat_integral_test
    ${OpenCV_LIBS}
    ${CONAN_LIBS})
endif()