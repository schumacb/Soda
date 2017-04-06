# ----------------------------------------------------------------------------
#
#
# ----------------------------------------------------------------------------

PROJECT(soda-cli)


# Add global definitions
ADD_DEFINITIONS(
    ${Soda_DEFINITIONS}
)


# ----------------------------------------------------------------------------
# External libraries

# Qt

# find includes in corresponding build directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
# run moc automatically when needed
SET(CMAKE_AUTOMOC ON)

FIND_PACKAGE(Qt5Core REQUIRED)
SET(LIBRARIES ${LIBRARIES} Qt5::Core)

INCLUDE_DIRECTORIES(${QT_INCLUDES})


# ----------------------------------------------------------------------------
# Internal libraries

# PluginManager
INCLUDE_DIRECTORIES(${pluginApi_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${pluginManager_INCLUDE_DIRS})
SET(LIBRARIES ${LIBRARIES} pluginManager)
# ----------------------------------------------------------------------------


# Build Application
AUX_SOURCE_DIRECTORY(. SRC_LIST)
ADD_EXECUTABLE(${PROJECT_NAME} ${SRC_LIST})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})
