#ifndef __APPMAIN_H
#define __APPMAIN_H

#include "app/app.hh"

namespace Fallment{



class AppControl:public App{
public:
    AppControl();
    virtual ~AppControl();

public:
    virtual bool onInit()override;
    virtual bool onUpdate()override;
    virtual void onFrame()override;
    virtual void onDestory()override;
    virtual void run()override;
};


}



#endif