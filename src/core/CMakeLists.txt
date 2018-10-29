# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(core VERSION 0.1.0)

# Add source files
aux_source_directory(${PROJECT_SOURCE_DIR} SOURCE_FILES)

#Debug
#message(FATAL_ERROR ${SOURCE_FILES})
#Debug

# Build Plugin
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}../include/${PROJECT_NAME} ${PROJECT_SOURCE_DIR})

# Dependencies -----------------------------------------------------------------

# Soda
target_link_libraries(${PROJECT_NAME})

