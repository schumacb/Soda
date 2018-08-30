# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------

project(framegrabber VERSION 0.2.0)

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
find_package(Qt5 COMPONENTS Core REQUIRED)
target_link_libraries(${PROJECT_NAME} Qt5::Core)

# OpenCV
find_package(OpenCV REQUIRED)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

