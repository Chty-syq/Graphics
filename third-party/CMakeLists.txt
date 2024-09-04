add_subdirectory(glad)
add_subdirectory(assimp)
add_subdirectory(poisson_disk_sampling)
add_subdirectory(tbb)
add_subdirectory(patterns)

add_library(imgui STATIC
        imgui/imgui.cpp
        imgui/imgui.h
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_demo.cpp
        imgui/backends/imgui_impl_opengl3.cpp
        imgui/backends/imgui_impl_opengl3.h
        imgui/backends/imgui_impl_glfw.cpp
        imgui/backends/imgui_impl_glfw.h
        )
target_link_libraries(imgui PUBLIC OpenGL::GL)
target_include_directories(imgui PUBLIC imgui imgui/backends)

add_library(third-party::imgui ALIAS imgui)