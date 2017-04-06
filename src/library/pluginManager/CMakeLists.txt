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

INCLUDE_DIRECTORIES(${QT_INCLUDES})


# ----------------------------------------------------------------------------
# Internal libraries

# PluginApi
INCLUDE_DIRECTORIES(${pluginApi_INCLUDE_DIRS})
# ----------------------------------------------------------------------------


# Build Library
AUX_SOURCE_DIRECTORY(. SRC_LIST)
ADD_LIBRARY(${PROJECT_NAME} STATIC ${SRC_LIST})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})
# Expose includes for other projects
SET(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)


