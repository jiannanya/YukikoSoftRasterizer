#ifndef __RENDERPASS_H
#define __RENDERPASS_H

#include "context.hh"

namespace Fallment{

class Context;

class RenderPass{
public:
    virtual void onInit()=0;
    virtual void onUpdate()=0;
    virtual void onFrame()=0;
    virtual void onDestory()=0;

    void setContext(std::shared_ptr<Context> _ctx);

public:

    std::shared_ptr<Context> m_ctx;

};

class RenderPassPhong:public RenderPass{
public:
    RenderPassPhong();
    ~RenderPassPhong();
    void onInit() override;
    virtual void onUpdate() override;
    virtual void onFrame() override;
    virtual void onDestory() override;

};

class RenderPassLine:public RenderPass{
public:
    RenderPassLine();
    ~RenderPassLine();
    void onInit() override;
    virtual void onUpdate() override;
    virtual void onFrame() override;
    virtual void onDestory() override;

};

class RenderPassFill:public RenderPass{
public:
    RenderPassFill();
    ~RenderPassFill();
    void onInit() override;
    virtual void onUpdate() override;
    virtual void onFrame() override;
    virtual void onDestory() override;

};

class RenderPassSSAO:public RenderPass{
public:
    RenderPassSSAO();
    ~RenderPassSSAO();
    void onInit() override;
    virtual void onUpdate() override;
    virtual void onFrame() override;
    virtual void onDestory() override;
};

}


#endif