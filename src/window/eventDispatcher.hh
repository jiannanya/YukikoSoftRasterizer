#ifndef __EVENT_DISPATCHER_HH
#define __EVENT_DISPATCHER_HH

#include "event.hh"

#include <memory>
#include <functional>
#include <vector>

namespace Fallment{

class EventDispatcher
{

    

public:
    EventDispatcher();
    ~EventDispatcher()=default;


    void addEventCallback(const EventCallbackFnType& callback,const EventType& eventtype);
    void removeEventCallback(const EventCallbackFnType& callback,const EventType& eventtype);

private:

     std::vector<std::vector<EventCallbackFnType>> EventCallbacks;

};






}

#endif