# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------

PROJECT(Utillity)


# Plugin version

SET (PLUGIN_VERSION_MAJOR 0)
SET (PLUGIN_VERSION_MINOR 1)
SET (PLUGIN_VERSION_PATCH 0)

CONFIGURE_FILE (
  "${PROJECT_SOURCE_DIR}/pluginconfig.hpp.in"
  "${PROJECT_BINARY_DIR}/pluginconfig.hpp"
  )

INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}")
FILE(GLOB CONFIG_HEADER_FILES "${PROJECT_BINARY_DIR}/*.hpp")
ADD_CUSTOM_TARGET(${PROJECT_NAME}ConfigHeaders SOURCES ${CONFIG_HEADER_FILES})

# Add global definitions
ADD_DEFINITIONS(
    ${Soda_DEFINITIONS}
)

# ----------------------------------------------------------------------------
# External libraries

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
# Local libraries

# pluginApi
INCLUDE_DIRECTORIES(${pluginApi_INCLUDE_DIRS})
# ----------------------------------------------------------------------------


# Build Plugin
AUX_SOURCE_DIRECTORY(. SRC_LIST)
ADD_LIBRARY(${PROJECT_NAME} SHARED ${SRC_LIST})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})
