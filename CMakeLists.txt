cmake_minimum_required(VERSION 3.25)
project(Graphics)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(third-party)

file(GLOB_RECURSE source_files CONFIGURE_DEPENDS src/*.cpp src/*.hpp)
add_executable(${PROJECT_NAME} ${source_files} src/common/utils.hpp)

if(UNIX)
    find_package(X11 REQUIRED)
    message(STATUS "X11_FOUND = ${X11_FOUND}")
    message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
    message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")
endif()

target_link_libraries(${PROJECT_NAME}
        glad
        glfw
        OpenGL::GL
        assimp
        imgui
        $<$<BOOL:${UNIX}>:${X11_LIBRARIES}>     # libX11 for Unix
        $<$<BOOL:${UNIX}>:${CMAKE_DL_LIBS}>     # libdl for ubuntu
        )
target_include_directories(${PROJECT_NAME} PUBLIC  # header-only package
        src
        third-party/stb_image
        third-party/glm
        )
