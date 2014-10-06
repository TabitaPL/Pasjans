#include "window.h"
#include "AngelHeader.h"

Window::Window():
    _horizontalMargin(1.0),
    _resolution(std::pair<int, int>(1920, 1080))
{
}
float Window::maxY() const
{
    return _maxY;
}

float Window::maxX() const
{
    return _maxX;
}

float Window::minY() const
{
    return _minY;
}

float Window::minX() const
{
    return _minX;
}



Window &Window::getInstance()
{
    static Window instance;
    return instance;
}

std::pair<int, int> Window::getResolution() const
{
    return _resolution;
}

void Window::setResolution(const std::pair<int, int> &resolution)
{
    _resolution = resolution;

    Vector2 topRight = theCamera.GetWorldMaxVertex();
    Vector2 bottomLeft = theCamera.GetWorldMinVertex();

    _minX = bottomLeft.X;
    _maxX = topRight.X;
    _minY = bottomLeft.Y;
    _maxY = topRight.Y;
    sysLog.Log("Window values: " + std::to_string(_minX) + " " + std::to_string(_maxX) + " " + std::to_string(_minY) + " " + std::to_string(_maxY) );

}

float Window::getWorldScreenWidth()
{
    return _maxX + MathUtil::Abs(_minX);
}
float Window::getHorizontalMargin() const
{
    return _horizontalMargin;
}

void Window::setHorizontalMargin(float horizontalMargin)
{
    _horizontalMargin = horizontalMargin;
}


