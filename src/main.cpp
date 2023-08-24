//#include "scene/render.hpp"
//#include "scene/gui.hpp"
#include "framework/ray_tracing/tracer.hpp"

int main() {
//    GraphRender::Init();
//    GUI::Init(GraphRender::window);
//    GraphRender::Render();

    Tracer tracer;
    tracer.Render();
    return 0;
}
