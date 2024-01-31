#ifndef __RENDERPASS_H
#define __RENDERPASS_H

#include "context.hh"

namespace Yukiko{

class RenderPass{
public:
    RenderPass();
    RenderPass(std::unique_ptr<Context> _ctx);
    ~RenderPass();
    void onInit();
    void onUpdate();
    void onFrame();
    void onDestory();

private:

    std::unique_ptr<Context> m_ctx;

};

}


#endif