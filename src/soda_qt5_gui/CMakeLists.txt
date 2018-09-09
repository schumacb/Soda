# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(soda_qt5_gui)

# Add source files
aux_source_directory(${PROJECT_SOURCE_DIR}/src SOURCE_FILES)
set(SOURCE_FILES forms/resources.qrc forms/MainWindow.qml forms/AboutDialogForm.ui.qml forms/ResourcePanel.ui.qml ${SOURCE_FILES})

if(SODA_BUILD_GUI)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTORCC ON)

    find_package(Qt5 COMPONENTS Core Widgets Gui Quick Qml QuickControls2)
    # Build Application
    message(INFO ${SOURCE_FILES})
    add_executable(${PROJECT_NAME} ${SOURCE_FILES})

    target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Quick Qt5::Qml Qt5::QuickControls2)
else()
  add_custom_target(${PROJECT_NAME} ${SOURCE_FILES})
endif()
