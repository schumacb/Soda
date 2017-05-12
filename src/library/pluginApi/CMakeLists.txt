# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------

PROJECT(PluginApi)

# Set API version
SET (PluginApi_VERSION_MAJOR 0)
SET (PluginApi_VERSION_MINOR 3)
SET (PluginApi_VERSION_PATCH 0)
CONFIGURE_FILE (
  "${PROJECT_SOURCE_DIR}/pluginapiconfig.hpp.in"
  "${PROJECT_BINARY_DIR}/pluginapiconfig.hpp"
  )
INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}")
FILE(GLOB CONFIG_HEADER_FILES "${PROJECT_BINARY_DIR}/*.hpp")
ADD_CUSTOM_TARGET(${PROJECT_NAME}ConfigHeaders SOURCES ${CONFIG_HEADER_FILES})

# Add source files
FILE(GLOB_RECURSE HEADER_FILES "*.hpp")
LIST(APPEND INCLUDES ${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR})


# ----------------------------------------------------------------------------
# Add external Libraries

# OpenCV
LIST(APPEND INCLUDES ${OpenCV_INCLUDES})
LIST(APPEND LIBRARIES ${OpenCV_LIBS})

# Qt
LIST(APPEND INCLUDES ${QT_INCLUDES})
LIST(APPEND LIBRARIES Qt5::Core)

# ----------------------------------------------------------------------------

# Build Library
ADD_CUSTOM_TARGET(${PROJECT_NAME}Headers SOURCES ${HEADER_FILES})

# Expose includes directories and libraries for other projects
SET(${PROJECT_NAME}_INCLUDES ${INCLUDES}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
SET(${PROJECT_NAME}_LIBS ${LIBRARIES}
    CACHE INTERNAL "${PROJECT_NAME}: Libraries" FORCE)
