# ----------------------------------------------------------------------------
#  Root CMake file for Soda
#
# ----------------------------------------------------------------------------

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

CMAKE_POLICY(SET CMP0053 NEW)

PROJECT(Soda)

# Options
OPTION(SODA_BUILD_GUI "Build Graphical User Interface." ON)
OPTION(SODA_BUILD_TESTS "Build Tests." ON)
OPTION(SODA_GENERATE_COVERAGE "Generate coverage information for Tests." OFF)

# Find includes in corresponding build directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

#CMake Modules
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

# Disable in source builds
SET(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
SET(CMAKE_DISABLE_SOURCE_CHANGES  ON)

IF ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  MESSAGE(SEND_ERROR "In-source builds are not allowed.")
ENDIF ()

# Setting default folders
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Compiler flaggs
IF(WIN32)
SET(CMAKE_CXX_FLAGS "-W4")
ELSE()
    SET(CMAKE_CXX_FLAGS " \
        -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic \
        -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual \
        -Wconversion -Wsign-conversion \
        -Weffc++ \
        "
        # unknown in clang 3.8.0
        # -Wmisleading-indentation
        # -Weverything
    )
ENDIF()

IF(SODA_GENERATE_COVERAGE)
  SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
  SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")

  INCLUDE(CodeCoverage)
  SET(LCOV_REMOVE_EXTRA "'${CMAKE_SOURCE_DIR}/test/*'" "'${CMAKE_SOURCE_DIR}/build/*'")
  SETUP_TARGET_FOR_COVERAGE(TestCoverageHtml tests coverage)
  SETUP_TARGET_FOR_COVERAGE_CODECOV(TestCoverage tests coverage)
ENDIF(SODA_GENERATE_COVERAGE)

# Makefile settings
SET(CMAKE_VERBOSE_MAKEFILE ON)
SET(CMAKE_COLOR_MAKEFILE   ON)

ADD_SUBDIRECTORY(external)
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)

# This target only serves to show CMake modules in IDEs.
FILE(GLOB_RECURSE CMAKE_MODULES "cmake/modules/*" )
ADD_CUSTOM_TARGET(CMakeModules SOURCES ${CMAKE_MODULES})

FILE(GLOB RESOURCE_FILES ".gitignore" ".travis.yml" "INSTALL" "LICENCE"
    "*.txt" "*.md" "*.sh")

# This target only serves to show resources in IDEs.
ADD_CUSTOM_TARGET(${PROJECT_NAME}Resources SOURCES ${RESOURCE_FILES})
