cmake_minimum_required(VERSION 3.5)

project(cli_interpreter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB interfaces "${CMAKE_SOURCE_DIR}/interfaces/*.h")
source_group("Interfaces" FILES ${interfaces})

file(GLOB headers "${CMAKE_SOURCE_DIR}/*.h")
source_group("Headers" FILES ${headers})

file(GLOB functions "${CMAKE_SOURCE_DIR}/functions/*.cpp")
source_group("Functions" FILES ${functions})

set(sources
    registrator.cpp
    main.cpp
)

add_executable(cli_interpreter ${interfaces} ${headers} ${sources} ${functions})
