#include "default_types.h"

#include "visualizer.h"

std::atomic<Object::Id> Object::ObjectsCount = 0u;

Object::Object() : unique_id_(ObjectsCount++) {}

Object::Id Object::getId() const {
    return unique_id_;
}

std::string Object::getName() const {
    return getTypeName() + std::to_string(unique_id_);
}

void Object::render(RendererInterface*) const {
    std::cout << "Rendering object " << getName() << '\n';
}

PlainText::PlainText(const char* ) {}

const char* PlainText::getTypeName() const {
    return "PlainText";
}

Circle::Circle(int) {}

const char* Circle::getTypeName() const {
    return "Circle";
}
