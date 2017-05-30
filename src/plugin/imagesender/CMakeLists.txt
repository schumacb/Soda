# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------

PROJECT(ImageSender)

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

# ----------------------------------------------------------------------------
# Add external libraries

# OpenCV
LIST(APPEND INCLUDES ${OpenCV_INCLUDES})
LIST(APPEND LIBRARIES ${OpenCV_LIBS})

# Qt
LIST(APPEND INCLUDES ${QT_INCLUDES})
LIST(APPEND LIBRARIES Qt5::Core)

# ----------------------------------------------------------------------------
# Add internal libraries

# pluginApi
LIST(APPEND INCLUDES ${PluginApi_INCLUDES})
LIST(APPEND LIBRARIES ${PluginApi_LIBS})

# core
LIST(APPEND INCLUDES ${Core_INCLUDES})
LIST(APPEND LIBRARIES ${Core_LIBS})

# ----------------------------------------------------------------------------

# Cleanup lists
LIST(REMOVE_DUPLICATES LIBRARIES)
LIST(REMOVE_DUPLICATES INCLUDES)

# Build Plugin
INCLUDE_DIRECTORIES(${INCLUDES})
ADD_LIBRARY(${PROJECT_NAME} SHARED ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})

# Expose includes directories and libraries for other projects
SET(${PROJECT_NAME}_INCLUDES ${INCLUDES}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
SET(${PROJECT_NAME}_LIBS ${PROJECT_NAME} ${LIBRARIES}
    CACHE INTERNAL "${PROJECT_NAME}: Libraries" FORCE)
