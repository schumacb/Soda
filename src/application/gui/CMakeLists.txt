# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------

PROJECT(soda)

# Add source files
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR} SOURCE_FILES)
LIST(APPEND INCLUDES ${PROJECT_SOURCE_DIR})

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

# Cleanup lists
LIST(REMOVE_DUPLICATES LIBRARIES)
LIST(REMOVE_DUPLICATES INCLUDES)

IF(SODA_BUILD_GUI)
  # Build Application
  INCLUDE_DIRECTORIES(${INCLUDES})
  ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE_FILES})
  TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})
ELSE()
  ADD_CUSTOM_TARGET(${PROJECT_NAME} ${SOURCE_FILES})
ENDIF()
