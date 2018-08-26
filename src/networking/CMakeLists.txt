# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(Network)

# Add source files
aux_source_directory(${PROJECT_SOURCE_DIR} SOURCE_FILES)

# Build library

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Dependencies --------------------------------------------------------------

# Qt
find_package(Qt5 COMPONENTS Core Network)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Network)
