cmake_minimum_required(VERSION 2.6)
project(SEMI_GLOBAL_MATCHING)

find_package(OpenCV REQUIRED)

include_directories(./SemiGlobalMatching)
aux_source_directory(./SemiGlobalMatching DIR_SRCS)
add_executable(../semi ${DIR_SRCS})
target_link_libraries(../semi ${OpenCV_LIBS})
