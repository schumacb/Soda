# ----------------------------------------------------------------------------
#
#
#
# ----------------------------------------------------------------------------

PROJECT(Network)

# Add source files
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR} SOURCE_FILES)

# Build library

ADD_LIBRARY(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Dependencies --------------------------------------------------------------

# Qt
FIND_PACKAGE(Qt5 COMPONENTS Core Network)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} Qt5::Core Qt5::Network)
