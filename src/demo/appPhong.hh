#ifndef __APPMAIN_H
#define __APPMAIN_H

#include "app/app.hh"

namespace Yukiko{

const char *TITLE = "Yukiko real time soft render";
const char *OBJ_PATH = "../assert/african_head.obj";
const char *OBJ_TEXTURE_PATH =  "../assert/african_head_diffuse.tga";

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr float FOV_INIT = 45.0f;

glm::vec3 CAM_POS_INIT = glm::vec3(1, 1, 3);
glm::vec3 CAM_TARGET_INIT = glm::vec3(0,0,0);
glm::vec3 CAM_UP_INIT = glm::vec3(0,1,0);

class AppPhong:public App{
public:
    AppPhong();
    virtual ~AppPhong();

public:
    virtual void onInit()override;
    virtual void onUpdate()override;
    virtual void onFrame()override;
    virtual void onDestory()override;
    virtual void run()override;
};


}



#endif