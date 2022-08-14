#pragma once

#include <cstdint>
#include <string>
#include <iostream>
#include <atomic>

#include "renderer_interface.h"

/// \brief: Object interface
class Object {
 public:
    using Id = uint64_t;

    Object();

    virtual ~Object() = default;

    virtual const char* getTypeName() const {
        return "Object";
    }

    /// \brief: render method tells RendererInterface how to draw stuff
    virtual void render(RendererInterface* v_i) const;

    Id getId() const;
    std::string getName() const;

 private:
    static std::atomic<Id> ObjectsCount;
    const Id unique_id_;
};

class PlainText : public Object {
 public:
    explicit PlainText(const char* text);

    const char* getTypeName() const override;
};

class Circle : public Object {
 public:
    explicit Circle(int radius);

    const char* getTypeName() const override;
};

// class CircleWithText : public Circle, public PlainText ... etc
