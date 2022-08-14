#pragma once

#include <memory>

#include "renderer_interface.h"

class RendererImpl;  // forward declaration

class Renderer : public RendererInterface {
 public:
    void drawLine(/* Point a, Point b, Color color, etc*/) override;
    void drawPoint(/* Point p, Color color, etc*/) override;

 private:
    RendererImpl* renderer_;
};

class Visualizer {
 public:
    template<typename It>
    void render(It begin, It end) {
        for (It obj_it = begin; obj_it != end; obj_it = std::next(obj_it)) {
            (*obj_it)->render(static_cast<RendererInterface*>(renderer_.get()));
        }
    }

 private:
    std::unique_ptr<Renderer> renderer_;
};
