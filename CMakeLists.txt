cmake_minimum_required(VERSION 2.8)

project( videocapture_basic)

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( videocapture_basic videocapture_basic.cpp )

target_link_libraries( videocapture_basic ${OpenCV_LIBS} )
