# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------

PROJECT(server)


# Add global definitions
ADD_DEFINITIONS(
    ${Soda_DEFINITIONS}
)


# ----------------------------------------------------------------------------
# External libraries

# Boost
FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED)
SET(LIBRARIES ${LIBRARIES} ${Boost_LIBRARIES})
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})


# OpenCV
FIND_PACKAGE(OpenCV REQUIRED)
SET(LIBRARIES ${LIBRARIES} ${OpenCV_LIBS})
INCLUDE_DIRECTORIES(${OpenCV_INCLUDES})


# Qt
# find includes in corresponding build directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
# run moc automatically when needed
SET(CMAKE_AUTOMOC ON)
# Qt Core module
FIND_PACKAGE(Qt5Core REQUIRED)
SET(LIBRARIES ${LIBRARIES} Qt5::Core)
# Qt Network module
FIND_PACKAGE(Qt5Network REQUIRED)
SET(LIBRARIES ${LIBRARIES} Qt5::Network)
# Qt includes
INCLUDE_DIRECTORIES(${QT_INCLUDES})
# ----------------------------------------------------------------------------


# Build library
AUX_SOURCE_DIRECTORY(. SRC_LIST)
ADD_LIBRARY(${PROJECT_NAME} STATIC ${SRC_LIST})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})
# Expose includes for other projects
SET(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
