#ifndef __APPMAIN_H
#define __APPMAIN_H

#include "app/app.hh"

namespace Fallment{

class AppLine:public App{
public:
    AppLine();
    virtual ~AppLine();

public:
    virtual bool onInit()override;
    virtual bool onUpdate()override;
    virtual void onFrame()override;
    virtual void onDestory()override;
    virtual void run()override;
};


}



#endif