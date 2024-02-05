#ifndef __APPMAIN_H
#define __APPMAIN_H

#include "app/app.hh"

namespace Fallment{



class AppPhong:public App{
public:
    AppPhong();
    virtual ~AppPhong();

public:
    virtual bool onInit()override;
    virtual bool onUpdate()override;
    virtual void onFrame()override;
    virtual void onDestory()override;
    virtual void run()override;
};


}



#endif