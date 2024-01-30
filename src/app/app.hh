#ifndef __APP_H
#define __APP_H

namespace Yukiko{

class App{

public:

    App();
    virtual ~App();

    virtual void onInit() = 0;
    virtual void onUpdate() = 0;
    virtual void onFrame() = 0;
    virtual void onDestory() = 0;


};

}

#endif