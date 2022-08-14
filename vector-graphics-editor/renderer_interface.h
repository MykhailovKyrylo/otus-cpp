#pragma once

class RendererInterface {
 public:
    virtual void drawLine(/* Point a, Point b, Color color, etc*/) = 0;
    virtual void drawPoint(/* Point p, Color color, etc*/) = 0;
};
