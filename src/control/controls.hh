#ifndef __CONTROLLER_H
#define __CONTROLLER_H

#include "window/event.hh"

#include <queue>
namespace Fallment{

class ControlOperation{
public:
    virtual void operator()() = 0;
    virtual ~ControlOperation(){}
};
class Controls{
public:
    virtual bool onInit() = 0;
    virtual bool onUpdate() = 0;
    virtual void onDestory() = 0;
    virtual void onEvent(const Event& e) = 0;
    virtual ~Controls(){}

protected:
    std::queue<std::unique_ptr<ControlOperation>> control_operation_queue;
};


class OrbitControls:public Controls{
public:
    OrbitControls();
    virtual ~OrbitControls(){}
public:
    bool onInit() override;
    bool onUpdate() override;
    void onDestory() override;
};


}


#endif