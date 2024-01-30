#ifndef __WINDOW_H
#define __WINDOW_H

#include "glfw/glfw3.h"

#include <vector>

namespace Yukiko{

class Window{
public:
    Window(unsigned w, unsigned h);
    ~Window();

    bool onInit();
    void onUpdate();
    void onDestory();

    void surfaceData(const std::vector<unsigned char> & data);


private:
    void processInput();

private:
    GLFWwindow* _window;

    unsigned witdh;
    unsigned height;

};

}

#endif