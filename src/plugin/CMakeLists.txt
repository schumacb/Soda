# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------

PROJECT(plugin)

ADD_SUBDIRECTORY(corenodes)
ADD_SUBDIRECTORY(blobdetect)

IF(SODA_BUILD_GUI)
ADD_SUBDIRECTORY(corenodesui)
ELSE(SODA_BUILD_GUI)
FILE(GLOB ALL_FILES "corenodesui/*")
ADD_CUSTOM_TARGET(CoreNodesUi SOURCES ${ALL_FILES})
ENDIF()

