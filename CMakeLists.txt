cmake_minimum_required(VERSION 2.8)
project( number_detector )
add_compile_options(-std=c++11)

# 添加OpenCV库
find_package( OpenCV REQUIRED )
find_package(Eigen3 REQUIRED)
include_directories( 
        include
        ${OpenCV_INCLUDE_DIR}
        ${EIGEN3_INCLUDE_DIR}
)

#生成可执行文件
add_executable( detector_demo demo/detector_demo.cpp src/number_detector.cpp)
target_link_libraries( detector_demo ${OpenCV_LIBS})