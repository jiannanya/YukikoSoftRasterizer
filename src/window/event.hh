
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

    Event(EventType et = EventType::None, bool handled = false):m_Type{et},m_Handled{handled}{}

public:
	bool m_Handled;	
    EventType m_Type;
};


class WindowSizeEvent: public Event{
public:
    WindowSizeEvent() = default;
    ~WindowSizeEvent() = default;

    WindowSizeEvent(int w, int h,EventType et, bool handled):width{w},height{h},Event{et,handled}{}

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

    MouseScrollEvent(double x, double y,EventType et, bool handled):xoffset{x},yoffset{y},Event{et,handled}{}
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


using EventCallbackFn = std::function<void(const Event&)>;

static int EventCallbackTypeId = 0;
struct EventCallbackFnType{

    EventCallbackFnType(EventCallbackFn f):fn{f},id{EventCallbackTypeId++}{}

    EventCallbackFn fn;
    int id;
};

}
#endif