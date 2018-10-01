# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------

project(blobdetect VERSION 0.2.0)

# Add source files
aux_source_directory(${PROJECT_SOURCE_DIR} SOURCE_FILES)

# Build Plugin
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

# Dependencies -----------------------------------------------------------------

# Soda
target_link_libraries(${PROJECT_NAME} interfaces)

# TODO: Remove Dependency to qt
# Qt
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)
find_package(Qt5 COMPONENTS Core REQUIRED)
target_link_libraries(${PROJECT_NAME} Qt5::Core)

# OpenCV
target_link_libraries(${PROJECT_NAME} opencv_adapter)

