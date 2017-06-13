# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------

PROJECT(Ui)

# Add source files
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR} SOURCE_FILES)
LIST(APPEND INCLUDES ${PROJECT_SOURCE_DIR})

# ----------------------------------------------------------------------------
# External libraries

# OpenCV
LIST(APPEND INCLUDES ${OpenCV_INCLUDES})
LIST(APPEND LIBRARIES ${OpenCV_LIBS})

# Qt
LIST(APPEND INCLUDES ${QT_INCLUDES})
LIST(APPEND LIBRARIES Qt5::Core Qt5::Widgets)

# Nodeeditor
LIST(APPEND INCLUDES ${NODEEDITOR_INCLUDE_DIR})
LIST(APPEND LIBRARIES ${NODEEDITOR_LIBS})
ADD_DEFINITIONS(${NODEEDITOR_DEFINES})
LINK_DIRECTORIES(${NODEEDITOR_LIB_DIR})

# ----------------------------------------------------------------------------
# Add internal libraries

# core
LIST(APPEND INCLUDES ${Core_INCLUDES})
LIST(APPEND LIBRARIES ${Core_LIBS})

# applciation
LIST(APPEND INCLUDES ${Application_INCLUDES})
LIST(APPEND LIBRARIES ${Application_LIBS})

# pluginApi
LIST(APPEND INCLUDES ${pluginApi_INCLUDES})
LIST(APPEND LIBRARIES ${pluginApi_LIBS})

# ----------------------------------------------------------------------------

# Cleanup lists
LIST(REMOVE_DUPLICATES INCLUDES)
LIST(REMOVE_DUPLICATES LIBRARIES)

# Build library
INCLUDE_DIRECTORIES(${INCLUDES})
ADD_LIBRARY(${PROJECT_NAME} STATIC ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})

# Expose includes directories and libraries for other projects
SET(${PROJECT_NAME}_INCLUDES ${INCLUDES}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
SET(${PROJECT_NAME}_LIBS ${PROJECT_NAME} ${LIBRARIES}
    CACHE INTERNAL "${PROJECT_NAME}: Libraries" FORCE)
