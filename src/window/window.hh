#ifndef __WINDOW_H
#define __WINDOW_H

#include "glfw/glfw3.h"

#include <vector>
#include <string>
namespace Yukiko{

class Window{
public:
    Window(std::string title, unsigned w, unsigned h);
    ~Window();

    bool onInit();
    void onFrame();
    void onUpdate();
    void onDestory();

    void surfaceData(const std::vector<unsigned char> & data);


private:
    void processInput();

private:
    GLFWwindow*                 _window;
    std::vector<unsigned char>  _buffer;
    std::string                 _title;
    unsigned                    _witdh;
    unsigned                    _height;

};

}

#endif