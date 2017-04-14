# ----------------------------------------------------------------------------
#
#
# ----------------------------------------------------------------------------

PROJECT(soda-cli)

# Add source files
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR} SOURCE_FILES)
LIST(APPEND INCLUDES ${PROJECT_SOURCE_DIR})

# ----------------------------------------------------------------------------
# External libraries

# Qt
LIST(APPEND LIBRARIES Qt5::Core)
LIST(APPEND INCLUDES ${QT_INCLUDES})

# ----------------------------------------------------------------------------
# Internal libraries

# PluginManager
LIST(APPEND INCLUDES ${pluginManager_INCLUDES})
LIST(APPEND LIBRARIES ${pluginManager_LIBS})
# ----------------------------------------------------------------------------

# Cleanup lists
LIST(REMOVE_DUPLICATES LIBRARIES)
LIST(REMOVE_DUPLICATES INCLUDES)

# Add global definitions
ADD_DEFINITIONS(
    ${Soda_DEFINITIONS}
)

# Build Application
INCLUDE_DIRECTORIES(${INCLUDES})
ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})
