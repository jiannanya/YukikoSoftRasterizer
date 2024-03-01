#ifndef __WINDOW_H
#define __WINDOW_H

#include "GLFW/glfw3.h"

#include <vector>
#include <string>

#include "framebuffer.hh"
#include "eventDispatcher.hh"

namespace Fallment{

template<typename Callable>
union storage
{
    storage() {}
    std::decay_t<Callable> callable;
};

template<int, typename Callable, typename Ret, typename... Args>
auto fnptr_(Callable&& c, Ret(*)(Args...))
{

    static storage<Callable> s;

    return [](Args... args) -> Ret {
        return Ret(s.callable(std::forward<Args>(args)...));
    };
}

template<typename Fn, typename Callable>
Fn* fnptr(Callable&& c)
{
    return fnptr_<0>(std::forward<Callable>(c), (Fn*)nullptr);
}


class Window{
public:
    Window(std::string title, unsigned w, unsigned h);
    ~Window();

    bool onInit();
    bool onUpdate();
    void onFrame();
    void onDestory();

    void setFramebuffer(std::shared_ptr<Framebuffer> fb);

    EventDispatcher* getEventDispatcher();


private:
    void processInput();
    void window_size_callback(GLFWwindow* window, int width, int height);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

private:
    GLFWwindow*                     _window;
    std::shared_ptr<Framebuffer>    _framebuffer;
    std::string                     _title;
    unsigned                        _witdh;
    unsigned                        _height;

private:
    std::unique_ptr<EventDispatcher>    _dispatcher;
};



}

#endif