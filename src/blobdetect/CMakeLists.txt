# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------

project(blobdetect)

# Add source files
aux_source_directory(${PROJECT_SOURCE_DIR} SOURCE_FILES)

# Build Plugin
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC .)
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

find_package(Qt5 COMPONENTS Core REQUIRED)
target_link_libraries(${PROJECT_NAME} Qt5::Core)
