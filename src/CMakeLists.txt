# ----------------------------------------------------------------------------
#
#
# ----------------------------------------------------------------------------

PROJECT(Source)


# Soda Version
SET(Soda_VERSION_MAJOR 0)
SET(Soda_VERSION_MINOR 1)
SET(Soda_VERSION_PATCH 2)


# Configure header file
CONFIGURE_FILE (
  "${PROJECT_SOURCE_DIR}/sodaconfig.hpp.in"
  "${PROJECT_BINARY_DIR}/sodaconfig.hpp"
  )

INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR})

FILE(GLOB CONFIG_HEADER_FILES "${PROJECT_BINARY_DIR}/*.hpp")
ADD_CUSTOM_TARGET(${PROJECT_NAME}ConfigHeaders SOURCES ${CONFIG_HEADER_FILES})

# Add subdirectories
ADD_SUBDIRECTORY(library)
ADD_SUBDIRECTORY(plugin)
ADD_SUBDIRECTORY(application)
