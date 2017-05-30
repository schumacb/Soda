PROJECT(nodeeditor_builder CXX)
INCLUDE(ExternalProject)

FIND_PACKAGE(Git REQUIRED)

ExternalProject_add(
    nodeeditor
    PREFIX ${CMAKE_BINARY_DIR}/nodeeditor
    GIT_REPOSITORY https://github.com/schumacb/nodeeditor.git
    TIMEOUT 10
    BUILD_COMMAND ninja -j 8
    CMAKE_ARGS
    "-DBUILD_EXAMPLES=OFF"
    UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
    )

ExternalProject_Get_Property(nodeeditor SOURCE_DIR)
ExternalProject_Get_Property(nodeeditor BINARY_DIR)

ADD_LIBRARY(nodes SHARED IMPORTED)
SET_PROPERTY(TARGET nodes PROPERTY IMPORTED_LOCATION ${BINARY_DIR}/lib/libnodes.so)

SET(NODEEDITOR_INCLUDE_DIR ${SOURCE_DIR}/include/
    CACHE INTERNAL "NodeEditor include Path")
SET(NODEEDITOR_LIBS nodes
    CACHE INTERNAL "NodeEditor include Path")
SET(NODEEDITOR_DEFINES -DNODE_EDITOR_SHARED
    CACHE INTERNAL "NodeEditor definitions")
SET(NODEEDITOR_DIR ${BINARY_DIR}
    CACHE INTERNAL "NodeEditor root directory")
SET(NODEEDITOR_LIB_DIR ${BINARY_DIR}/lib/
    CACHE INTERNAL "NodeEditor library directory")
