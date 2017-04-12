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
AUX_SOURCE_DIRECTORY(. SOURCE_FILES)
ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})
ADD_TEST(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

IF(GENERATE_COVERAGE AND (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU"))
        # this is an undocumented option for changing the output extension from *.cpp.ext
        # to *.ext; As there is no reasonable way to obtain the list of object files
        # this seems to be the best option to generate the naming gcov expects.
#      SET(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)


  TARGET_COMPILE_OPTIONS(${PROJECT_NAME} PRIVATE --coverage -fprofile-arcs -ftest-coverage)
  TARGET_LINK_LIBRARIES(${PROJECT_NAME} PRIVATE -fprofile-arcs -ftest-coverage)
  ADD_CUSTOM_TARGET(${PROJECT_NAME}_TestCoverage
      COMMAND gcov -o ${PROJECT_SOURCE_DIR} ${SOURCE_FILES}
      WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
      COMMENT "Collecting gcov coverage information"
        )
ELSE()

ENDIF()
