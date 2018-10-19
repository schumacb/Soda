# ----------------------------------------------------------------------------
#
#
# ----------------------------------------------------------------------------

# Project configuration
project(soda_opencv_gui)
aux_source_directory(${PROJECT_SOURCE_DIR} SOURCE_FILES)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

##### Dependencies #####
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# Soda internal
target_link_libraries(${PROJECT_NAME} blobdetect)

# OpenCV
find_package(OpenCV REQUIRED)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARIES})
