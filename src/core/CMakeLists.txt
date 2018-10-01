# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------

project(soda_core VERSION 0.1.0)

# Add source files
aux_source_directory(${PROJECT_SOURCE_DIR}/src SOURCE_FILES)

# Build Plugin
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Dependencies -----------------------------------------------------------------

# Soda
target_link_libraries(${PROJECT_NAME} interfaces)

