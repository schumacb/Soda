# ----------------------------------------------------------------------------
#
#
# ----------------------------------------------------------------------------

PROJECT(soda-cli)

# Add source files
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR} SOURCE_FILES)
LIST(APPEND INCLUDES ${PROJECT_SOURCE_DIR})

# ----------------------------------------------------------------------------
# Add external libraries

# Qt
LIST(APPEND INCLUDES ${QT_INCLUDES})
LIST(APPEND LIBRARIES Qt5::Core)

# ----------------------------------------------------------------------------
# Add internal libraries

# Core
LIST(APPEND INCLUDES ${Core_INCLUDES})
LIST(APPEND LIBRARIES ${Core_LIBS})

# ----------------------------------------------------------------------------

# Cleanup lists
LIST(REMOVE_DUPLICATES LIBRARIES)
LIST(REMOVE_DUPLICATES INCLUDES)

# Build Application
INCLUDE_DIRECTORIES(${INCLUDES})
ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})
