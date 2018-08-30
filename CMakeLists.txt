# ----------------------------------------------------------------------------
#  Root CMake file for Soda
#
# ----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(Soda)
include_directories(src/includes CACHE)

# Options
option(SODA_BUILD_GUI "Build Graphical User Interface." ON)
option(SODA_BUILD_TESTS "Build Tests." ON)
option(SODA_GENERATE_COVERAGE "Generate coverage information for Tests." OFF)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#CMake Modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

# Disable in source builds
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
	message(SEND_ERROR "In-source builds are not allowed.")
endif()

# Setting default folders
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Compiler flaggs
if(MSVC)
    set(CMAKE_CXX_FLAGS "-W4"
        #" -WX"
    )
elseif(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_FLAGS " \
        -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic \
        -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual \
        -Wconversion -Wsign-conversion \
        -Weffc++ -Wmisleading-indentation"
        #"-Weverything"
        #" -Werror"
    )
elseif(CMAKE_CXX_COMPILER EQUAL Clang)
    set(CMAKE_CXX_FLAGS " \
        -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic \
        -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual \
        -Wconversion -Wsign-conversion \
        -Weffc++ -Wmisleading-indentation -Weverything -Werror"
    )
else()
    MESSAGE(FATAL_ERROR "No compiler flags defined for current compiler:" ${CMAKE_CXX_COMPILER})
endif()

if(SODA_GENERATE_COVERAGE)
  set(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
  set(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")

  include(CodeCoverage)
  set(LCOV_REMOVE_EXTRA "'${CMAKE_SOURCE_DIR}/test/*'" "'${CMAKE_SOURCE_DIR}/build/*'")
  setup_target_for_coverage(TestCoverageHtml tests coverage)
  setup_target_for_coverage_codecov(TestCoverage tests coverage)
endif(SODA_GENERATE_COVERAGE)

# Makefile settings
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)

add_subdirectory(src/interfaces)
add_subdirectory(src/framegrabber)
add_subdirectory(src/blobdetect)
add_subdirectory(src/networking)
add_subdirectory(src/soda_cli)
add_subdirectory(src/soda_qt5_gui)

# This target only serves to show CMake modules in IDEs.
file(GLOB_RECURSE CMAKE_MODULES "cmake/modules/*" )
add_custom_target(CMakeModules SOURCES ${CMAKE_MODULES})

file(GLOB RESOURCE_FILES ".gitignore" ".travis.yml" "INSTALL" "LICENCE"
    "*.txt" "*.md" "*.sh")

# This target only serves to show resources in IDEs.
add_custom_target(Resources SOURCES ${RESOURCE_FILES})
