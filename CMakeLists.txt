cmake_minimum_required(VERSION 4.1)
project(COP3530-P2-NBA-Performance-Rankings LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(COP3530-P2-NBA-Performance-Rankings src/main.cpp
        src/CSVReader.cpp
        src/MergeSort.cpp
        src/HeapSort.cpp
)
target_compile_features(COP3530-P2-NBA-Performance-Rankings PRIVATE cxx_std_17)
target_link_libraries(COP3530-P2-NBA-Performance-Rankings PRIVATE SFML::Graphics)

set(DATA_SOURCE "${CMAKE_SOURCE_DIR}/resources/font.ttf")
set(DATA_DEST "${CMAKE_BINARY_DIR}/resources/font.ttf")
file(COPY ${DATA_SOURCE} DESTINATION ${CMAKE_BINARY_DIR}/data/)

set(DATA_SOURCE "${CMAKE_SOURCE_DIR}/resources/games_details.csv")
set(DATA_DEST "${CMAKE_BINARY_DIR}/resources/games_details.csv")
file(COPY ${DATA_SOURCE} DESTINATION ${CMAKE_BINARY_DIR}/data/)