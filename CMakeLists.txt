cmake_minimum_required(VERSION 3.25)
project(Graphics)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
add_subdirectory(third-party/glad)

file(GLOB_RECURSE source_files CONFIGURE_DEPENDS src/*.cpp src/*.hpp)
add_executable(${PROJECT_NAME} ${source_files})

target_link_libraries(${PROJECT_NAME}
        glad
        glfw
        OpenGL::GL
        ${CMAKE_DL_LIBS}
        )
target_include_directories(${PROJECT_NAME} PUBLIC  # header-only package
        src
        third-party/stb_image
        third-party/glm
        )
