#include "document.h"

Document Document::LoadFromFile(const char* filename) {
    std::cout << "Trying to read document from file: " << filename << '\n';
    return Document{};
}

bool Document::saveToFile(const char* filename) const {
    std::cout << "Trying to save document into file: " << filename << '\n';
    return true;
}
