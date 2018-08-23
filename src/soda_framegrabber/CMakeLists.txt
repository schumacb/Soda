# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------

PROJECT(SodaFramegrabber)

# Set plugin version
SET (PLUGIN_VERSION_MAJOR 0)
SET (PLUGIN_VERSION_MINOR 1)
SET (PLUGIN_VERSION_PATCH 0)
CONFIGURE_FILE (
  "${PROJECT_SOURCE_DIR}/pluginconfig.hpp.in"
  "${PROJECT_BINARY_DIR}/pluginconfig.hpp"
  )
LIST(APPEND INCLUDES "${PROJECT_BINARY_DIR}")
FILE(GLOB CONFIG_HEADER_FILES "${PROJECT_BINARY_DIR}/*.hpp")
ADD_CUSTOM_TARGET(${PROJECT_NAME}ConfigHeaders SOURCES ${CONFIG_HEADER_FILES})

# Add source files
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR} SOURCE_FILES)
LIST(APPEND INCLUDES ${PROJECT_SOURCE_DIR})

# Build Plugin
INCLUDE_DIRECTORIES(${INCLUDES})
ADD_LIBRARY(${PROJECT_NAME} SHARED ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})

# Dependencies -----------------------------------------------------------------

# Soda
FIND_PACKAGE(Soda COMPONENTS PluginApi REQUIRED)
#INCLUDE_DIRECTORIES(${SodaPluginApi_INCLUDE_DIRS})

# Qt
FIND_PACKAGE(Qt5 COMPONENTS Core)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} Qt5::Core)

