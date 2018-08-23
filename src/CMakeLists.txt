# ----------------------------------------------------------------------------
#
#
# ----------------------------------------------------------------------------

PROJECT(Source)

# Set soda version
SET(Soda_VERSION_MAJOR 0)
SET(Soda_VERSION_MINOR 1)
SET(Soda_VERSION_PATCH 2)
CONFIGURE_FILE (
  "${PROJECT_SOURCE_DIR}/sodaconfig.hpp.in"
  "${PROJECT_BINARY_DIR}/sodaconfig.hpp"
  )
LIST(APPEND ${INCLUDES} ${PROJECT_BINARY_DIR})

FILE(GLOB CONFIG_HEADER_FILES "${PROJECT_BINARY_DIR}/*.hpp")
ADD_CUSTOM_TARGET(${PROJECT_NAME}ConfigHeaders SOURCES ${CONFIG_HEADER_FILES})

# Add subdirectories
ADD_SUBDIRECTORY(soda_plugin_api)
ADD_SUBDIRECTORY(soda_framegrabber)
ADD_SUBDIRECTORY(soda_blob_detection)
ADD_SUBDIRECTORY(soda_plugin_manager)
ADD_SUBDIRECTORY(soda_networking)
ADD_SUBDIRECTORY(soda_qt5_gui)
ADD_SUBDIRECTORY(soda_cli)
