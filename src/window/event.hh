
#ifndef __EVENT_HH
#define __EVENT_HH

#include <functional>

namespace Fallment{


enum class EventType{
    None            =0,
    WindowSize      =1,
    WindowClose     =2,
    MouseScroll     =3,
    MousePos        =4,
    MousePush       =5,
    MouseRelease    =6,
    MouseDrag       =7,
    KeyBoard        =8,

};

class Event {		
public:
    Event() = default;
    ~Event() = default;

public:
	bool m_Handled;	
    EventType m_Type;
};


class WindowSizeEvent: public Event{
public:
    WindowSizeEvent() = default;
    ~WindowSizeEvent() = default;

public:

    int width;
    int height;
};

class WindowCloseEvent : public Event {	
public:
	WindowCloseEvent() = default;
    ~WindowCloseEvent() = default;
};

class MouseScrollEvent: public Event{
public:
    MouseScrollEvent() = default;
    ~MouseScrollEvent() = default;
public:
    double xoffset;
    double yoffset;
};

class MousePosEvent: public Event{
public:
    MousePosEvent() = default;
    ~MousePosEvent() = default;
public:
    double xpos;
    double ypos;
    
};

class KeyEvent: public Event{
public:
    KeyEvent() = default;
    ~KeyEvent() = default;

public:
    int key;
};


using EventCallbackFn = std::function<void(Event&)>;

static int EventCallbackTypeId = 0;
struct EventCallbackFnType{

    EventCallbackFnType(EventCallbackFn f):fn{f},id{id++}{}

    EventCallbackFn fn;
    int id;
};

}
#endif