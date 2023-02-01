cmake_minimum_required(VERSION 3.22.3)
project(test_cpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(lib)
add_subdirectory(lib)

set(DLL_FILE "D:\\Program Files\\JetBrains\\CLion 2022.1.2\\bin\\mingw\\bin\\")

include_directories("C:\\Program Files\\MySQL\\MySQL Server 8.0\\include")

link_libraries("C:\\\\Program Files\\\\MySQL\\\\MySQL Server 8.0\\\\lib\\\\libmysql.lib")

aux_source_directory(. SOURCE_SRC)
add_executable(test_cpp ${SOURCE_SRC})

get_property(HAS_LIB_LIBRARY GLOBAL PROPERTY "HAS_LIB_LIBRARY")

if (HAS_LIB_LIBRARY)
    target_link_libraries(test_cpp lib)
endif ()

file(COPY "${DLL_FILE}libstdc++-6.dll" DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY "${DLL_FILE}libgcc_s_seh-1.dll" DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY "C:\\Program Files\\MySQL\\MySQL Server 8.0\\lib\\libmysql.dll" DESTINATION "${CMAKE_BINARY_DIR}")