message(STATUS "------------------------START-------------------------------------")
set(TARGET_NAME land-builder)

# Automatically add the current source- and build directories to the include path.
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Collect source files
file(GLOB_RECURSE SRCS ${PROJECT_SOURCE_DIR}/src *.cpp)

add_executable(${TARGET_NAME} ${SRCS})

install(
  TARGETS ${TARGET_NAME}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

file(GLOB_RECURSE LAND_CONFIGS ${PROJECT_SOURCE_DIR}/etc/*.json)

install(
  FILES ${LAND_CONFIGS}
  PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
  DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}
)

message(STATUS "-----------------------DONE--------------------------------------")

