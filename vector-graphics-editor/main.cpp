#include "document.h"
#include "visualizer.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    auto doc = Document::LoadFromFile("/document0.vge");

    doc.addObject<PlainText>("test text plain");

    const int circle_radius = 42;
    doc.addObject<Circle>(circle_radius);

    doc.saveToFile("/document1.vge");

    Visualizer visualizer;

    const auto objects = doc.getObjects();
    visualizer.render(objects.begin(), objects.end());
}
