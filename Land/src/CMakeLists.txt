cmake_minimum_required(VERSION 3.07)
set(TARGET_NAME landCalculator)

message(STATUS "---------------------------------------------------")
message(STATUS "${TARGET_NAME} - Importing dependencies ")

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# Automatically add the current source- and build directories to the include path.
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(RapidJSON)

include_directories("../build/usr/local/include/")
include_directories("./src/")
#include_directories("./src/landConfigurartion")

# Collect source files
file(GLOB_RECURSE SRCS ${PROJECT_SOURCE_DIR}/src *.cpp)

add_executable(${TARGET_NAME} ${SRCS})

message(STATUS "${PROJECT_SOURCE_DIR} - PROJECT_SOURCE_DIR ")
message(STATUS "${CMAKE_INSTALL_BINDIR} - CMAKE_INSTALL_BINDIR ")

install(
  TARGETS ${TARGET_NAME}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

file(GLOB_RECURSE LAND_CONFIGS ${PROJECT_SOURCE_DIR}/etc/*.json)

install( FILES ${LAND_CONFIGS}
  PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
  DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}
)

message(STATUS "-----------------------DONE--------------------------------------")

