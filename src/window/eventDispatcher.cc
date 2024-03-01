#include "eventDispatcher.hh"


namespace Fallment{

EventDispatcher::EventDispatcher(){

    using UT = std::underlying_type_t<EventType>;
    for (UT i = static_cast<UT>(EventType::None) + 1; i < static_cast<UT>(EventType::MousePos) + 1; ++i) {
        //EventType et = static_cast<EventType>(i);
        EventCallbacks[i] = std::vector<EventCallbackFnType>();
}

}

void EventDispatcher::addEventCallback(const EventCallbackFnType& callback,const EventType& eventtype){
    EventCallbacks[static_cast<int>(eventtype)].emplace_back(callback);
}

void EventDispatcher::removeEventCallback(const EventCallbackFnType& callback,const EventType& eventtype){
    EventCallbacks[static_cast<int>(eventtype)].erase(
        std::remove_if(
            EventCallbacks[static_cast<int>(eventtype)].begin(),
            EventCallbacks[static_cast<int>(eventtype)].end(),
            [&callback](EventCallbackFnType& fn){
                return callback.id == fn.id;
            }
            ),
        EventCallbacks[static_cast<int>(eventtype)].end()
    );
}

}