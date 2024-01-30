
#include "window/window.hh"

namespace Yukiko{

Window::Window(unsigned w, unsigned h):witdh{w},height{h}{

}

Window::~Window(){

}

bool Window::onInit(){
    
    if (!glfwInit())
        return -1;

    
    _window = glfwCreateWindow(witdh, height, "YukikoSoftRasterizer", NULL, NULL);
    if (!_window)
    {
        
        return false;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(_window);

    return true;
}

void Window::onUpdate(){
    
}

void Window::onDestory(){
    glfwTerminate();
}

void Window::surfaceData(const std::vector<unsigned char> & data){
    
}

void Window::processInput()
{

    if(!_window)return;

    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(_window, true);
}

}