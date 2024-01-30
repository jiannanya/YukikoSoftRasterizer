#ifndef __SOFTAPP_H
#define __SOFTAPP_H

#include "app/app.hh"

namespace Yukiko{

class SoftApp:public App{
public:
    SoftApp();
    virtual ~SoftApp();

    virtual void onInit() override;
    virtual void onUpdate() override;
    virtual void onFrame() override;
    virtual void onDestory() override;

    void run();

private:

    

};

}

#endif