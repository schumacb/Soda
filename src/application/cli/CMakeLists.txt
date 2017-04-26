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

# Build Application
INCLUDE_DIRECTORIES(${INCLUDES})
ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})
