project(ogl-tester)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

include_directories(${GLFW_INCLUDE_DIRS})

add_executable(triangle triangle.cpp common.h)
target_link_libraries(triangle glue ${GLFW_STATIC_LIBRARIES})

add_executable(textures textures.cpp common.h)
target_link_libraries(textures glue ${GLFW_STATIC_LIBRARIES})
file(COPY pinguin.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
