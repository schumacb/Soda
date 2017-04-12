# ----------------------------------------------------------------------------
#
#
# ----------------------------------------------------------------------------

PROJECT(PluginManagerTest)


# Add global definitions
ADD_DEFINITIONS(
    ${Soda_DEFINITIONS}
)


# ----------------------------------------------------------------------------
# External libraries

# Catch
SET(INCLUDE_DIRS ${INCLUDE_DIRS} ${CATCH_INCLUDE_DIR} ${COMMON_INCLUDES})

# Qt

# find includes in corresponding build directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
# run moc automatically when needed
SET(CMAKE_AUTOMOC ON)

FIND_PACKAGE(Qt5Core REQUIRED)
SET(LIBRARIES ${LIBRARIES} Qt5::Core)

SET(INCLUDE_DIRS ${INCLUDE_DIRS} ${QT_INCLUDES})


# ----------------------------------------------------------------------------
# Internal libraries

# PluginManager
SET(INCLUDE_DIRS ${INCLUDE_DIRS} ${pluginManager_INCLUDE_DIRS})
SET(LIBRARIES ${LIBRARIES} pluginManager)
# ----------------------------------------------------------------------------


# Build Application
LIST(REMOVE_DUPLICATES INCLUDE_DIRS)
INCLUDE_DIRECTORIES(${INCLUDE_DIRS})
AUX_SOURCE_DIRECTORY(. SRC_LIST)
ADD_EXECUTABLE(${PROJECT_NAME} ${SRC_LIST})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})
ADD_TEST(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
