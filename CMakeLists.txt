cmake_minimum_required(VERSION 3.17)
project(imageEditor)

set(CMAKE_CXX_STANDARD 14)

add_executable(imageEditor main.cpp)

find_package(SFML 2.5 COMPONENTS system window graphics)
target_link_libraries(imageEditor sfml-system sfml-window sfml-graphics)

set(OpenCV_DIR "C:/opencv-4.5.1/build")
find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui imgcodecs)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(imageEditor ${Open_CV_LIBS})
