cmake_minimum_required(VERSION 3.22.3)
project(lib)

aux_source_directory(. SOURCE_SRC)

if (SOURCE_SRC)
    add_library(lib ${SOURCE_SRC})
    set_property(GLOBAL PROPERTY HAS_LIB_LIBRARY true)
endif ()