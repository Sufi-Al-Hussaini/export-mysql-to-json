cmake_minimum_required(VERSION 3.5)
project(export-mysql-to-json)
enable_language(C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -std=c99 -pedantic -g")
set(SOURCE_FILES parson.c parson.h main.c)

add_executable(export-mysql-to-json ${SOURCE_FILES})