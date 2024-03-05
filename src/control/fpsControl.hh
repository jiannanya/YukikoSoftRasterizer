#ifndef __FPS_CONTROLLER_H
#define __FPS_CONTROLLER_H


#include "controls.hh"
#include "renderer/camera.hh"
#include "window/event.hh"
#include "window/eventDispatcher.hh"
#include "spdlog/spdlog.h"

#include <memory>

namespace Fallment{


class FpsControls:public Controls{
    friend class ControlOperation;
public:
    FpsControls() = default;
    virtual ~FpsControls() = default;

    FpsControls(std::shared_ptr<Camera> camera);

public:
    bool onInit() override;
    bool onUpdate() override;
    void onDestory() override;
    void onEvent(const Event& e) override;

private:

    void onMousePosEvent(const Event& e);
    void onMouseScrollEvent(const Event& e);
    void onWindowSizeEvent(const Event& e);

    std::shared_ptr<Camera>  m_camera;

    bool    firstMouse;
    float   lastX;
    float   lastY;
    float   yaw;
    float   pitch;


};


}
#endif