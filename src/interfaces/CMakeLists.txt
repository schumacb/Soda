cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(interfaces)

# Add source files
aux_source_directory(${PROJECT_SOURCE_DIR}/src SOURCE_FILES)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/include)

find_package(Qt5 COMPONENTS Core REQUIRED)
target_link_libraries(${PROJECT_NAME} INTERFACE Qt5::Core)
