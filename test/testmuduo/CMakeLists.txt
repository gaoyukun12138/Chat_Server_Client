cmake_minimum_required(VERSION 3.0) #系统要求的最小版本，要在3.0以上
project(main) #工程名字


#配置编译选项
# 类似于g++中的-o, -g
#将CMAKE_CXX_FLAGS修改值为CMAKE_CXX_FLAGS -g
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g) #-g可调试

#如果是在项目的根目录下创建CMakeList.txt文件， 需要：
#指定搜索的子目录
#add_subdirectory(testmuduo)

#配置头文件搜索路径
#include_directories()

#配置库文件搜索路径
#link_directories()


#生成可执行文件
#还可以设置需要编译的源文件列表

set(SRC_LIST muduo_servce.cpp)
add_executable(server ${SRC_LIST})

#设置可执行文件最终存储的路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#也可以设置生成的动态库，使用LIBRARY_OUTPUT_DIRECTORY变量 放到lib目录中



# 或者是
# add_executable(server muduo_servce.cpp)

#若文件比较多
#把. 指定路径下的所有源文件放入变量名
#aux_source_directory(. SRC_LIST)
#add_executable(server ${SRC_LIST})

#链接库muduo_net muduo_base pthread温念
target_link_libraries(server muduo_net muduo_base pthread)

#cmake .执行就可以了
