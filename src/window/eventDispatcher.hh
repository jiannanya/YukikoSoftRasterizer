#ifndef __EVENT_DISPATCHER_HH
#define __EVENT_DISPATCHER_HH

#include "event.hh"

#include <memory>
#include <functional>

namespace Fallment{

class EventDispatcher
{

    

public:
    EventDispatcher()=default;
    ~EventDispatcher()=default;

    EventDispatcher(std::unique_ptr<Event>&& Event);

    void SetEventCallback(const EventCallbackFn& callback);

private:

    EventCallbackFn EventCallback;

};






}

#endif