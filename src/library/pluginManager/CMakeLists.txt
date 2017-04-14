# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------

PROJECT(pluginManager)

AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR} SOURCE_FILES)
LIST(APPEND INCLUDES ${PROJECT_SOURCE_DIR})

# ----------------------------------------------------------------------------
# External libraries

# Qt
LIST(APPEND INCLUDES ${QT_INCLUDES})
LIST(APPEND LIBRARIES Qt5::Core)

# ----------------------------------------------------------------------------
# Internal libraries

# PluginApi
LIST(APPEND INCLUDES ${pluginApi_INCLUDES})
LIST(APPEND LIBRARIES ${pluginApi_LIBS})
# ----------------------------------------------------------------------------

# Cleanup lists
LIST(REMOVE_DUPLICATES LIBRARIES)
LIST(REMOVE_DUPLICATES INCLUDES)

# Add global definitions
ADD_DEFINITIONS(
    ${Soda_DEFINITIONS}
)

# Build Library
INCLUDE_DIRECTORIES(${INCLUDES})
ADD_LIBRARY(${PROJECT_NAME} STATIC ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC ${LIBRARIES})

# Expose includes directories and libraries for other projects
SET(${PROJECT_NAME}_INCLUDES ${INCLUDES}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
SET(${PROJECT_NAME}_LIBS ${PROJECT_NAME} ${LIBRARIES}
    CACHE INTERNAL "${PROJECT_NAME}: Libraries" FORCE)


