#ifndef __WINDOW_H
#define __WINDOW_H

#include "GLFW/glfw3.h"

#include <vector>
#include <string>

#include "framebuffer.hh"

namespace Fallment{

class Window{
public:
    Window(std::string title, unsigned w, unsigned h);
    ~Window();

    bool onInit();
    bool onUpdate();
    void onFrame();
    void onDestory();

    void setFramebuffer(std::shared_ptr<Framebuffer> fb);


private:
    void processInput();

private:
    GLFWwindow*                     _window;
    std::shared_ptr<Framebuffer>    _framebuffer;
    std::string                     _title;
    unsigned                        _witdh;
    unsigned                        _height;

};

}

#endif