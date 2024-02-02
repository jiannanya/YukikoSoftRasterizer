
#include "window/window.hh"

namespace Fallment{

Window::Window(std::string title, unsigned w, unsigned h):_witdh{w},_height{h}{

}

Window::~Window(){

}

bool Window::onInit(){
    
    if (!glfwInit())
        return -1;

    
    _window = glfwCreateWindow(_witdh, _height, _title.c_str(), NULL, NULL);
    if (!_window)
    {
        
        return false;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(_window);

    return true;
}

void Window::onFrame(){
    unsigned char* p = _buffer.data();
    glDrawPixels(_witdh, _height,GL_RGBA, GL_UNSIGNED_BYTE, p);
    glfwSwapBuffers(_window);
}

void Window::onUpdate(){
    glfwPollEvents();
    
}

void Window::onDestory(){
    glfwTerminate();
}

void Window::surfaceData(const std::vector<unsigned char> & data){
    _buffer = data;
}

void Window::processInput()
{

    if(!_window)return;

    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(_window, true);
}

}