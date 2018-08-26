cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(interfaces)

# Add source files
aux_source_directory(${PROJECT_SOURCE_DIR} SOURCE_FILES)

add_library(${PROJECT_NAME} INTERFACE ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} INTERFACE .)

find_package(Qt5 COMPONENTS Core REQUIRED)
target_link_libraries(${PROJECT_NAME} INTERFACE Qt5::Core)
