PROJECT(tests C CXX)

FILE(GLOB_RECURSE SOURCE_FILES "*.?pp")

IF(SODA_BUILD_TESTS OR SODA_GENERATE_COVERAGE)
  # Add extermal Libraries
  # Prepare "Catch" library for other executables
  SET(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/catch)
  ADD_LIBRARY(Catch INTERFACE)
  TARGET_INCLUDE_DIRECTORIES(Catch INTERFACE ${CATCH_INCLUDE_DIR})
  LIST(APPEND INCLUDES ${CATCH_INCLUDE_DIR})
  LIST(APPEND LIBRARIES Catch)

  # Qt
  LIST(APPEND INCLUDES ${QT_INCLUDES})

  # Add internal Libraries
  LIST(APPEND INCLUDES ${PluginApi_INCLUDES})
  LIST(APPEND LIBRARIES ${PluginApi_LIBS})
  LIST(APPEND INCLUDES ${PluginManager_INCLUDES})
  LIST(APPEND LIBRARIES ${PluginManager_LIBS})

  ENABLE_TESTING()

  INCLUDE_DIRECTORIES(${INCLUDES})
  ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE_FILES})
  SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
  TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})
ELSE(SODA_BUILD_TESTS)
  ADD_CUSTOM_TARGET(${PROJECT_NAME} SOURCES ${SOURCE_FILES})
ENDIF(SODA_BUILD_TESTS)
