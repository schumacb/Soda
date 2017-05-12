# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------

PROJECT(soda)

# Add source files
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR} SOURCE_FILES)
LIST(APPEND INCLUDES ${PROJECT_SOURCE_DIR})
FILE(GLOB RESOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.qrc")
FILE(GLOB UI_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")

# add Qt resources
qt5_add_resources(RESOURCES_RCC ${RESOURCE_FILES})
qt5_wrap_ui(UI_RCC ${UI_FILES})

# ----------------------------------------------------------------------------
# Add external libraries

# Qt
LIST(APPEND INCLUDES ${QT_INCLUDES})
LIST(APPEND LIBRARIES Qt5::Core Qt5::Widgets Qt5::Gui Qt5::OpenGL Qt5::Multimedia)

LIST(APPEND INCLUDES ${NODEEDITOR_INCLUDE_DIR})
LIST(APPEND LIBRARIES ${NODEEDITOR_LIBS})
ADD_DEFINITIONS(${NODEEDITOR_DEFINES})
LINK_DIRECTORIES(${NODEEDITOR_LIB_DIR})

# ----------------------------------------------------------------------------
# Add internal libraries

# PluginManager
LIST(APPEND INCLUDES ${PluginManager_INCLUDES})
LIST(APPEND LIBRARIES ${PluginManager_LIBS})

# Requiredplugins
LIST(APPEND INCLUDES ${Utillity_INCLUDES})
LIST(APPEND LIBRARIES ${Utillity_LIBS})

# ----------------------------------------------------------------------------
# Cleanup lists
LIST(REMOVE_DUPLICATES LIBRARIES)
LIST(REMOVE_DUPLICATES INCLUDES)

IF(SODA_BUILD_GUI)
  # Build Application
  INCLUDE_DIRECTORIES(${INCLUDES})
  ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE_FILES} ${RESOURCES_RCC} ${UI_RCC})
  TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})
  ADD_CUSTOM_TARGET(${PROJECT_NAME}Resources SOURCES ${RESOURCES_FILES} ${UI_FILES})
ELSE()
  ADD_CUSTOM_TARGET(${PROJECT_NAME} SOURCES ${SOURCE_FILES} ${RESOURCES_FILES} ${UI_FILES})
ENDIF()
