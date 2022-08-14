#pragma once

#include <type_traits>
#include <memory>
#include <unordered_map>
#include <utility>
#include <list>

#include "default_types.h"

class ObjectStorage {
 public:
    /// \brief: User receives a weak ptr in order someone deletes it in other place
    template<class ObjectT,
        typename std::enable_if_t<std::is_base_of_v<Object, ObjectT>, bool> = true>
    class ObjectHandler {
     public:
        explicit ObjectHandler(ObjectStorage* storage) : storage_(storage) {}

        /// \brief: use this weak pointer to modify object
        std::weak_ptr<ObjectT> object;

        bool removeObject() {
            if (object.expired()) {
                return false;
            }

            return storage_->removeObject(object->getId());
        }

     private:
        ObjectStorage* storage_;
    };

 public:
    template<class ObjectT,
        typename std::enable_if_t<std::is_base_of_v<Object, ObjectT>, bool> = true>
    ObjectStorage::ObjectHandler<ObjectT> addObject(std::shared_ptr<ObjectT>&& object) {
        ObjectHandler<ObjectT> obj_handler(this);
        obj_handler.object = object;

        objects_.insert({object->getId(), std::move(object)});

        return obj_handler;
    }

    bool removeObject(Object::Id id);

    std::list<std::shared_ptr<const Object>> getObjects() const;

 private:
    /// \note: contains shared pointers, however objects' life is totally manages by this class.
    /// Shared because we need to create weak pointers for ObjectHandlers
    std::unordered_map<Object::Id, std::shared_ptr<Object>> objects_;
};
