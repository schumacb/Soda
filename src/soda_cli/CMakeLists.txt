# ----------------------------------------------------------------------------
#
#
# ----------------------------------------------------------------------------


project(soda-cli)
aux_source_directory(${PROJECT_SOURCE_DIR} SOURCE_FILES)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

#### Dependencies ####
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# Soda
target_link_libraries(${PROJECT_NAME} core blobdetect)

# Qt
find_package(Qt5 COMPONENTS Core)
target_link_libraries(${PROJECT_NAME} Qt5::Core)

# OpenCV
find_package(OpenCV REQUIRED)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARIES})


