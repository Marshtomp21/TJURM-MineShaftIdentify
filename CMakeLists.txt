cmake_minimum_required(VERSION 3.5)

# 项目信息
project(tjurm-mineshaftidentify)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)

# 编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -g -w")

# 查找 OpenCV
find_package(OpenCV REQUIRED)
if (NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV not found!")
endif()

# 包含目录
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR})

# 设置源文件
file(GLOB_RECURSE SOURCES src/*.cpp)

# 添加可执行文件
add_executable(tjurm-mineshaftidentify main.cpp ${SOURCES})

# 链接 OpenCV 库
target_link_libraries(tjurm-mineshaftidentify ${OpenCV_LIBS})
