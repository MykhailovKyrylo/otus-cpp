#include "object_storage.h"

bool ObjectStorage::removeObject(Object::Id id) {
    if (!objects_.count(id)) {
        return false;
    }

    objects_.erase(id);
    return true;
}

std::list<std::shared_ptr<const Object>> ObjectStorage::getObjects() const {
    std::list<std::shared_ptr<const Object>> objects;

    for (auto& [id, object] : objects_) {
        objects.push_back(object);
    }

    return objects;
}
