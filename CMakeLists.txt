# ----------------------------------------------------------------------------
#  Root CMake file for Soda
#
# ----------------------------------------------------------------------------

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(Soda)

# Options
OPTION(SODA_BUILD_GUI "Build Graphical User Interface." ON)
OPTION(SODA_BUILD_TESTS "Build Tests." OFF)
OPTION(SODA_GENERATE_COVERAGE "Generate coverage information for Tests." OFF)

# Core dependencies
FIND_PACKAGE(OpenCV REQUIRED)
FIND_PACKAGE(Qt5 COMPONENTS
             Core Network
             REQUIRED)
# GUI dependencies
IF(SODA_BUILD_GUI)
  FIND_PACKAGE(Qt5 COMPONENTS
    Widgets
    REQUIRED)
  ADD_DEFINITIONS(${Qt5Widgets_DEFINITIONS})
  SET(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
ENDIF()
# Test dependencies
IF(SODA_BUILD_TESTS)
  FIND_PACKAGE(Qt5 COMPONENTS
      Test
      REQUIRED)
ENDIF()


# Find includes in corresponding build directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# Run moc automatically when needed
SET(CMAKE_AUTOMOC ON)

#CMake Modules
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

# Set C++ Standard
SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

# Disable in source builds
SET(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
SET(CMAKE_DISABLE_SOURCE_CHANGES  ON)

IF ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  MESSAGE(SEND_ERROR "In-source builds are not allowed.")
ENDIF ()

# Setting default folders
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Compiler flaggs
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

# Ceck build environment
IF($ENV{TRAVIS})
  IF($ENV{TRAVIS} STREQUAL "true")
    MESSAGE(STATUS "This is a Travis CI build.")
    SET(IS_TRAVIS_BUILD ON)
    SET(SODA_BUILD_TESTS ON)
    SET(SODA_GNERATE_COVERAGE ON)
  ENDIF()
ENDIF()

IF(SODA_BUILD_TESTS AND SODA_GENERATE_COVERAGE)
  SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
  SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
ENDIF()

# Makefile settings
SET(CMAKE_VERBOSE_MAKEFILE ON)
SET(CMAKE_COLOR_MAKEFILE   ON)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)

FILE(GLOB RESOURCE_FILES ".gitignore" ".travis.yml" "INSTALL" "LICENCE"
    "*.txt" "*.md" "*.sh")

# This target only serves to show resources in IDEs.
ADD_CUSTOM_TARGET(${PROJECT_NAME}Resources SOURCES ${RESOURCE_FILES})
