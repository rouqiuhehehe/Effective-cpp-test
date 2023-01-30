cmake_minimum_required(VERSION 3.22.3)
project(test_cpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(lib)
add_subdirectory(lib)

aux_source_directory(. SOURCE_SRC)
add_executable(test_cpp ${SOURCE_SRC})

get_property(HAS_LIB_LIBRARY GLOBAL PROPERTY "HAS_LIB_LIBRARY")

if (HAS_LIB_LIBRARY)
    target_link_libraries(test_cpp lib)
endif ()