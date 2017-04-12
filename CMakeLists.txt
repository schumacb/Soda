# ----------------------------------------------------------------------------
#  Root CMake file for Soda
#
# ----------------------------------------------------------------------------

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(Soda)

# Options
OPTION(BUILD_TESTS "" ON)

# Set C++ Standard
SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

# Disable in source builds
SET(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
SET(CMAKE_DISABLE_SOURCE_CHANGES  ON)

IF ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  MESSAGE(SEND_ERROR "In-source builds are not allowed.")
ENDIF ()

# Global Definitions
SET(${PROJECT_NAME}_DEFINITIONS
    -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
    -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual
    -Wconversion -Wsign-conversion
    -Weffc++
    # unknown in clang 3.8.0
    # -Wmisleading-indentation
    # -Weverything
    CACHE INTERNAL "${PROJECT_NAME}: Global Definitions" FORCE)

# Makefile settings
SET(CMAKE_VERBOSE_MAKEFILE ON)
SET(CMAKE_COLOR_MAKEFILE   ON)

ADD_SUBDIRECTORY(external)
ADD_SUBDIRECTORY(src)

IF(BUILD_TESTS)
  ENABLE_TESTING()
  ADD_SUBDIRECTORY(test)
ENDIF()

FILE(GLOB TEXT_FILES "*.txt")

ADD_CUSTOM_TARGET(${PROJECT_NAME}_NonSource SOURCES ${TEXT_FILES})
