#ifndef __APP_H
#define __APP_H

#include "mesh.hh"
#include "shader.hh"
#include "window.hh"
#include "camera.hh"
#include "framebuffer.hh"
#include "rasterizer.hh"
#include "texture.hh"
#include "context.hh"
#include "math.hh"
#include "triangle.hh"
#include "light.hh"
#include "scene.hh"
#include "context.hh"
#include "controls.hh"

namespace Fallment{

class App{

public:

    virtual bool onInit() = 0;
    virtual bool onUpdate() = 0;
    virtual void onFrame() = 0;
    virtual void onDestory() = 0;
    virtual void run() = 0;

public:
    
    std::unique_ptr<RenderPassPhong> m_renderpass;
    std::unique_ptr<Controls>   m_controls;
    std::unique_ptr<Window>     m_window;
    std::shared_ptr<Context>    m_ctx;
};

}

#endif