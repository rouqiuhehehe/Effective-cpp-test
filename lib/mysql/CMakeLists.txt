cmake_minimum_required(VERSION 3.22.3)
project(test_cpp)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

link_libraries("C:\\\\Program Files\\\\MySQL\\\\MySQL Server 8.0\\\\lib\\\\libmysql.lib")
include_directories("C:\\Program Files\\MySQL\\MySQL Server 8.0\\include")

aux_source_directory(. SOURCE_SRC)
add_library(mymysql SHARED ${SOURCE_SRC})