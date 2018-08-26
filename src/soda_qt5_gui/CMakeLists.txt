# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(soda)

# Add source files
aux_source_directory(${PROJECT_SOURCE_DIR} SOURCE_FILES)

if(SODA_BUILD_GUI)
  # Build Application
  add_executable(${PROJECT_NAME} ${SOURCE_FILES})
  find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
  target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets)
else()
  add_custom_target(${PROJECT_NAME} ${SOURCE_FILES})
endif()
