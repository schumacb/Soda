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
LIST(APPEND LIBRARIES Qt5::Core Qt5::Widgets)

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
