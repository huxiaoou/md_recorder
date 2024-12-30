cmake_minimum_required(VERSION 3.5)
project(demo)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
include_directories(${PROJECT_SOURCE_DIR}/include)

set(SRC_LIST src/main.cpp)
find_library(LIB_QTOOLS libqtools.so HINTS ${PROJECT_SOURCE_DIR}/lib)
add_executable(md_recorder ${SRC_LIST})
target_link_libraries(md_recorder ${LIB_QTOOLS})

# set(SRC_LIST src/main.cpp src/QOperator.cpp src/QListener.cpp src/QAnalyst.cpp)