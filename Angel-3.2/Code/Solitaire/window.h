#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>

#define theWindow Window::getInstance()

class Window
{
public:
    static Window& getInstance();

    std::pair<int, int> getResolution() const;
    void setResolution(const std::pair<int, int> &resolution);
    float getWorldScreenWidth();

    float getHorizontalMargin() const;
    void setHorizontalMargin(float horizontalMargin); //margin for left and right side of screen

    float minX() const;
    float minY() const;
    float maxX() const;
    float maxY() const;

private:
    Window();
    std::pair<int, int> _resolution; //in pixels
    float _horizontalMargin;
    float _minX;
    float _minY;
    float _maxX;
    float _maxY;

};

#endif // WINDOW_H
