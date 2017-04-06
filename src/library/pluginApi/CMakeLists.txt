# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------

PROJECT(pluginApi)


# Add global definitions
ADD_DEFINITIONS(
    ${Soda_DEFINITIONS}
)


# API version

SET (PluginApi_VERSION_MAJOR 0)
SET (PluginApi_VERSION_MINOR 1)
SET (PluginApi_VERSION_PATCH 0)

CONFIGURE_FILE (
  "${PROJECT_SOURCE_DIR}/pluginapiconfig.hpp.in"
  "${PROJECT_BINARY_DIR}/pluginapiconfig.hpp"
  )

INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}")
FILE(GLOB CONFIG_HEADER_FILES "${PROJECT_BINARY_DIR}/*.hpp")
ADD_CUSTOM_TARGET(${PROJECT_NAME}ConfigHeaders SOURCES ${CONFIG_HEADER_FILES})

# ----------------------------------------------------------------------------
# External Libraries

# OpenCV
FIND_PACKAGE(OpenCV REQUIRED)
SET(LIBRARIES ${LIBRARIES} ${OpenCV_LIBS})
INCLUDE_DIRECTORIES(${OpenCV_INCLUDES})


# Qt

# find includes in corresponding build directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
# run moc automatically when needed
SET(CMAKE_AUTOMOC ON)

FIND_PACKAGE(Qt5Core REQUIRED)
SET(LIBRARIES ${LIBRARIES} Qt5::Core)

INCLUDE_DIRECTORIES(${QT_INCLUDES})
# ----------------------------------------------------------------------------


# Build Library

FILE(GLOB_RECURSE HEADER_FILES "*.hpp")
ADD_CUSTOM_TARGET(${PROJECT_NAME}Headers SOURCES ${HEADER_FILES})

# Expose includes for other projects
SET(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
