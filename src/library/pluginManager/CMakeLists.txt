# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------

PROJECT(pluginManager)

# Add global definitions
ADD_DEFINITIONS(
    ${Soda_DEFINITIONS}
)

# ----------------------------------------------------------------------------
# External libraries

# Qt
# find includes in corresponding build directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
# run moc automatically when needed
SET(CMAKE_AUTOMOC ON)

FIND_PACKAGE(Qt5Core REQUIRED)
SET(LIBRARIES ${LIBRARIES} Qt5::Core)

SET(INCLUDE_DIRS ${INCLUDE_DIRS} ${QT_INCLUDES})


# ----------------------------------------------------------------------------
# Internal libraries

# PluginApi
SET(INCLUDE_DIRS ${INCLUDE_DIRS} ${pluginApi_INCLUDE_DIRS})
# ----------------------------------------------------------------------------


# Build Library
LIST(REMOVE_DUPLICATES INCLUDE_DIRS)
INCLUDE_DIRECTORIES(${INCLUDE_DIRS})
AUX_SOURCE_DIRECTORY(. SRC_LIST)
ADD_LIBRARY(${PROJECT_NAME} STATIC ${SRC_LIST})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})
# Expose includes for other projects
SET(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR} ${INCLUDE_DIRS}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)


