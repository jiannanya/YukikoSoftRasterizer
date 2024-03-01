#include "eventDispatcher.hh"


namespace Fallment{

EventDispatcher::EventDispatcher(){

    // using UT = std::underlying_type_t<EventType>;
    // for (UT i = static_cast<UT>(EventType::None) + 1; i < static_cast<UT>(EventType::MousePos) + 1; ++i) {
    //     //EventType et = static_cast<EventType>(i);
        
    // }

    EventCallbacks = std::vector<EventCallbackFnType>();

}

void EventDispatcher::addEventCallback(const EventCallbackFnType& callback){
    EventCallbacks.emplace_back(callback);
}

void EventDispatcher::removeEventCallback(const EventCallbackFnType& callback){
    EventCallbacks.erase(
        std::remove_if(
            EventCallbacks.begin(),
            EventCallbacks.end(),
            [&callback](EventCallbackFnType& fn){
                return callback.id == fn.id;
            }
            ),
        EventCallbacks.end()
    );
}

void EventDispatcher::dispatch(const Event& e){
    for(auto&cb: EventCallbacks){
        cb.fn(e);
    }
}

}