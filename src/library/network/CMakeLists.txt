# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------

PROJECT(server)

# Add source files
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR} SOURCE_FILES)
LIST(APPEND INCLUDES ${PROJECT_SOURCE_DIR})

# ----------------------------------------------------------------------------
# External libraries

# OpenCV
LIST(APPEND LIBRARIES ${OpenCV_LIBS})
LIST(APPEND INCLUDES ${OpenCV_INCLUDES})

# Qt
LIST(APPEND LIBRARIES Qt5::Core Qt5::Network)
LIST(APPEND INCLUDES ${QT_INCLUDES})
# ----------------------------------------------------------------------------

# Add global definitions
ADD_DEFINITIONS(
    ${Soda_DEFINITIONS}
)

# Build library
INCLUDE_DIRECTORIES(${INCLUDES})
ADD_LIBRARY(${PROJECT_NAME} STATIC ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})

# Expose includes directories and libraries for other projects
SET(${PROJECT_NAME}_INCLUDES ${INCLUDES}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
SET(${PROJECT_NAME}_LIBS ${PROJECT_NAME} ${LIBRARIES}
    CACHE INTERNAL "${PROJECT_NAME}: Libraries" FORCE)
