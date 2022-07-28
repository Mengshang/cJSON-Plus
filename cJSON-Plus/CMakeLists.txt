# CMakeList.txt: cJSON-Plus 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("cJSON-Plus")

# 将源代码添加到此项目的可执行文件。
# add_executable (cJSON-Plus  "cJSON-Plus.h")

include_directories(./cJSON)
include_directories(./include)
add_executable(cJSON-Plus "include/cJSON_Plus.h")
target_sources(cJSON-Plus PUBLIC "cJSON/cJSON.c")
target_sources(cJSON-Plus PUBLIC "src/cJSON_Plus.cpp")
target_sources(cJSON-Plus PUBLIC "src/test_main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET cJSON-Plus PROPERTY CXX_STANDARD 11)
endif()

# TODO: 如有需要，请添加测试并安装目标。
