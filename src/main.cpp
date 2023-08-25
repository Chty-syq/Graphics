#include "scene/render.hpp"
#include "scene/gui.hpp"

int main() {
    GraphRender::Init();
    GUI::Init(GraphRender::window);
    GraphRender::Render();
    return 0;
}
