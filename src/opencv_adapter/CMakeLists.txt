# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(opencv_adapter CXX)

# Add source files
aux_source_directory(${PROJECT_SOURCE_DIR}/src SOURCE_FILES)

# Build library

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} INTERFACE include/)

# Dependencies --------------------------------------------------------------

# OpenCV
find_package(OpenCV REQUIRED )
target_link_libraries(${PROJECT_NAME} INTERFACE ${OpenCV_LIBS})
