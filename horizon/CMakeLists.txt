cmake_minimum_required(VERSION 2.8.4)
project(HorizonGeometry)



find_package( OpenCV REQUIRED )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")


add_executable(HorizonGeometry HorizonGeometry.cpp ${SOURCE_FILES})

target_link_libraries( HorizonGeometry ${OpenCV_LIBS} )
