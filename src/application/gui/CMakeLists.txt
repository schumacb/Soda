# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------

PROJECT(soda)

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

FIND_PACKAGE(Qt5Widgets REQUIRED)
SET(LIBRARIES ${LIBRARIES} Qt5::Widgets)

INCLUDE_DIRECTORIES(${QT_INCLUDES})

# ----------------------------------------------------------------------------


# Build Application
AUX_SOURCE_DIRECTORY(. SRC_LIST)
ADD_EXECUTABLE(${PROJECT_NAME} ${SRC_LIST})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})

