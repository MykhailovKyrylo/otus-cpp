#pragma once

#include <iostream>
#include <type_traits>
#include <memory>
#include <utility>
#include <list>

#include "object_storage.h"

class Document {
 public:
    static Document LoadFromFile(const char* filename);

 public:
    bool saveToFile(const char* filename) const;

    template<class ObjectT,
        class... Args,
        typename std::enable_if_t<std::is_base_of_v<Object, ObjectT>, bool> = true,
    typename std::enable_if_t<std::is_constructible_v<ObjectT, Args...>, bool> = true>
    ObjectStorage::ObjectHandler<ObjectT> addObject(Args... args) {
        auto obj_ptr = std::make_shared<ObjectT>(args...);

        std::cout << "Adding object: " << obj_ptr->getName() << '\n';

        return storage_.addObject(std::move(obj_ptr));
    }

    auto getObjects() const {
        return storage_.getObjects();
    }

 public:
    ObjectStorage storage_;
};
