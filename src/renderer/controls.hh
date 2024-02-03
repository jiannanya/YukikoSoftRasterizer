#ifndef __CONTROLLER_H
#define __CONTROLLER_H

namespace Fallment{

class Controls{
public:
    virtual bool onInit() = 0;
    virtual bool onUpdate() = 0;
    virtual void onDestory() = 0;
    virtual ~Controls(){}
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