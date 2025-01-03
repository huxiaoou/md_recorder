cmake_minimum_required(VERSION 3.5)
project(md_recorder)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
include_directories(${PROJECT_SOURCE_DIR}/include)

set(SRC_LIST src/main.cpp
    src/QConfig.cpp
    src/QOperator.cpp
    src/QListener.cpp
    src/QAnalyst.cpp
    src/QAutomatic.cpp
)

find_library(LIB_QTOOLS libqtools.so)
find_library(LIB_MD libthostmduserapi_se.so)

add_executable(md_recorder ${SRC_LIST})
target_link_libraries(md_recorder ${LIB_QTOOLS})
target_link_libraries(md_recorder ${LIB_MD})
