
#include "window/window.hh"

#include "spdlog/spdlog.h"

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
    if(_framebuffer.get()){
        std::unique_lock<std::mutex>(_framebuffer->m_color_mutex);
        glDrawPixels(_witdh, _height,GL_RGBA, GL_UNSIGNED_BYTE, _framebuffer->getColorBuffer());
        glfwSwapBuffers(_window);
    }else{
        spdlog::error("Window surface doesnt have any famebuffer data useful");
    }


}

void Window::onUpdate(){
    glfwPollEvents();
    
}

void Window::onDestory(){
    glfwTerminate();
}

void Window::setFramebuffer(std::shared_ptr<Framebuffer> fb){
    _framebuffer = fb;
}

void Window::processInput()
{

    if(!_window)return;

    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(_window, true);
}

}