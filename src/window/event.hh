
#ifndef __EVENT_HH
#define __EVENT_HH

#include <functional>

namespace Fallment{


enum class EventType{
    None            =0,
    WindowSize      =1,
    WindowClose     =2,
    MouseScroll     =3,
    MousePos        =4

};

class Event {		
public:
    Event() = default;
    ~Event() = default;

public:
	bool m_Handled;						
};


class WindowSizeEvent: public Event{
public:
    WindowSizeEvent() = default;
    ~WindowSizeEvent() = default;
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
};

class MousePosEvent: public Event{
public:
    MousePosEvent() = default;
    ~MousePosEvent() = default;
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