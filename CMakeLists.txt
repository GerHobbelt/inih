cmake_minimum_required(VERSION 3.10)

# cpp std
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# compile_commands.json for intellisense
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES 0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# include directories
file(GLOB include_directories "${CMAKE_CURRENT_SOURCE_DIR}/cpp")
include_directories(BEFORE CMAKE_CURRENT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cpp")

# test extended classes
file(GLOB source_files "${CMAKE_CURRENT_SOURCE_DIR}/cpp/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/ini.c" "${CMAKE_CURRENT_SOURCE_DIR}/tests/vector_test.cpp")
add_executable(vector_test.app ${source_files}) 

# copy resources
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/tests/vector_test.ini" "${CMAKE_CURRENT_BINARY_DIR}/vector_test.ini" COPYONLY)

