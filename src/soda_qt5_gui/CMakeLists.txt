# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(soda_qt5_gui)

# Add source files
aux_source_directory(${PROJECT_SOURCE_DIR} SOURCE_FILES)

if(SODA_BUILD_GUI)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    # Instruct CMake to run moc automatically when needed
    set(CMAKE_AUTOMOC ON)
    # Create code from a list of Qt designer ui files
    set(CMAKE_AUTOUIC ON)

    set(CMAKE_AUTORCC ON)
    find_package(Qt5 COMPONENTS Core Widgets CONFIG REQUIRED)
    # Build Application
    add_executable(${PROJECT_NAME} aboutdialog.ui ${SOURCE_FILES})

    target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets)
else()
  add_custom_target(${PROJECT_NAME} ${SOURCE_FILES})
endif()
