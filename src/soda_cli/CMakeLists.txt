# ----------------------------------------------------------------------------
#
#
# ----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(soda-cli)

# Add source files
aux_source_directory(${PROJECT_SOURCE_DIR} SOURCE_FILES)

# Build Application
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Dependencies
find_package(Qt5 COMPONENTS Core)
target_link_libraries(${PROJECT_NAME} Qt5::Core)

find_package(OpenCV REQUIRED)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARIES})

target_link_libraries(${PROJECT_NAME} framegrabber)
