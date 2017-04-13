# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------

PROJECT(pluginManager)

# Add global definitions
ADD_DEFINITIONS(
    ${Soda_DEFINITIONS}
)

SET(PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")

# ----------------------------------------------------------------------------
# External libraries

# Qt
# find includes in corresponding build directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
# run moc automatically when needed
SET(CMAKE_AUTOMOC ON)

FIND_PACKAGE(Qt5Core REQUIRED)
SET(LIBRARIES ${LIBRARIES} Qt5::Core)

SET(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${QT_INCLUDES})


# ----------------------------------------------------------------------------
# Internal libraries

# PluginApi
SET(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${pluginApi_INCLUDE_DIRS})
# ----------------------------------------------------------------------------


# Build Library
SET(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${PROJECT_SOURCE_DIR})
LIST(REMOVE_DUPLICATES INCLUDE_DIRECTORIES)
INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES})
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR} PROJECT_SOURCE_FILES)
ADD_LIBRARY(${PROJECT_NAME} STATIC ${PROJECT_SOURCE_FILES} ${PROJECT_INCLUDE_FILES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC ${LIBRARIES})
# Expose includes for other projects
SET(${PROJECT_NAME}_INCLUDE_DIRS ${INCLUDE_DIRECTORIES}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

FILE(GLOB PROJECT_INCLUDE_FILES "${PROJECT_INCLUDE_DIR}/*.hpp")
ADD_CUSTOM_TARGET(${PROJECT_NAME}Includes SOURCES ${PROJECT_INCLUDE_FILES})

IF(BUILD_TESTS)
  # Catch
  SET(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${CATCH_INCLUDE_DIR} ${COMMON_INCLUDES})
  # Library to Test  
  SET(LIBRARIES ${LIBRARIES} ${PROJECT_NAME})
  AUX_SOURCE_DIRECTORY(test TEST_SOURCE_FILES)
  ADD_EXECUTABLE(${PROJECT_NAME}Test ${TEST_SOURCE_FILES})
  TARGET_LINK_LIBRARIES(${PROJECT_NAME}Test ${LIBRARIES})
  ADD_TEST(NAME ${PROJECT_NAME}Test COMMAND ${PROJECT_NAME}Test)

  IF(GENERATE_COVERAGE AND (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU"))
    TARGET_COMPILE_OPTIONS(${PROJECT_NAME} PRIVATE --coverage -fprofile-arcs -ftest-coverage)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} PRIVATE -fprofile-arcs -ftest-coverage)
    ADD_CUSTOM_TARGET(${PROJECT_NAME}TestCoverage
        COMMAND gcov -o ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_FILES}
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        COMMENT "Collecting gcov coverage information")
  ENDIF() # GENERATE_COVERAGE
ENDIF() # BUILD_TESTS
