# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------

PROJECT(PluginApi)

# Set API version
SET (PluginApi_Version 0.2.0)
SET (PluginApi_VERSION_MAJOR 0)
SET (PluginApi_VERSION_MINOR 2)
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

# Build Library
ADD_LIBRARY(${PROJECT_NAME} INTERFACE)
TARGET_COMPILE_DEFINITIONS(${PROJECT_NAME} INTERFACE ${PROJECT_NAME}=1)
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} INTERFACE .)

ADD_CUSTOM_TARGET(${PROJECT_NAME}Headers HEADERS ${HEADER_FILES})

INSTALL(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include)
INSTALL(EXPORT ${PROJECT_NAME}Targets FILE ${PROJECT_NAME}Targets.cmake NAMESPACE Soda:: DESTINATION lib/cmake/${PROJECT_NAME})

INCLUDE(CMakePackageConfigHelpers)
write_basic_package_version_file(${PROJECT_NAME}ConfigVersion.cmake VERSION ${PluginApi_Version} COMPATIBILITY SameMajorVersion)

INSTALL(FILES ${PROJECT_NAME}Config.cmake ${PROJECT_NAME}ConfigVersion.cmake DESTINATION lib/cmake/${PROJECT_NAME})
