# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(soda_qt5_gui)
aux_source_directory(${PROJECT_SOURCE_DIR}/src SOURCE_FILES)
set(SOURCE_FILES resources/resources.qrc ${SOURCE_FILES})

if(SODA_BUILD_GUI)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTORCC ON)

    add_executable(${PROJECT_NAME} ${SOURCE_FILES})

    find_package(Qt5 COMPONENTS Core Widgets Gui)
    target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Gui)
else()
  add_custom_target(${PROJECT_NAME} ${SOURCE_FILES})
endif()
