cmake_minimum_required(VERSION 3.0) #系统要求的最小版本，要在3.0以上
project(chat)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g) #-g可调试

#最终的可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#配置头文件的搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/server)
include_directories(${PROJECT_SOURCE_DIR}/include/server/db)
include_directories(${PROJECT_SOURCE_DIR}/include/server/model)
include_directories(${PROJECT_SOURCE_DIR}/include/server/redis)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty)


#加载子目录
add_subdirectory(src)

