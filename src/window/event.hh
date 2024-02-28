
#ifndef __EVENT_HH
#define __EVENT_HH

#include <functional>

namespace Fallment{



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

}
#endif