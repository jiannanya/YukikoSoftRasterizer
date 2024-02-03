#ifndef __CONTEXT_HH
#define __CONTEXT_HH

#include "math.hh"
#include "mesh.hh"
#include "shader.hh"
#include "window.hh"
#include "camera.hh"
#include "framebuffer.hh"
#include "texture.hh"
#include "rasterizer.hh"
#include "scene.hh"
#include "renderpass.hh"

namespace Fallment{

class Context{
    friend class RenderPassPhong;
public:
    Context();
    ~Context();

    //void setWindow(std::unique_ptr<Window> window);
    void setCamera(std::unique_ptr<Camera>&& camera);
    void setShader(std::unique_ptr<Shader>&& shader);
    void setVertexShaderIn(std::unique_ptr<VertexInData>&& _data);
    void setVertexShaderOut(std::unique_ptr<VertexOutData>&& _data);
    void setFragmentShaderIn(std::unique_ptr<FragmentInData>&& _data);
    void setFragmentShaderOut(std::unique_ptr<FragmentOutData>&& _data);
    void setFrameBuffer(std::shared_ptr<Framebuffer>&& fb);
    //void setTexture(std::unique_ptr<Texture> tex);
    void setScene(std::unique_ptr<Scene>&& sce);
    void setRasterizer(std::unique_ptr<Rasterizer>&& rast);
    //void setRenderPass(std::unique_ptr<RenderPass> rp);
    
    

    Framebuffer* getFrameBuffer()const;
    //Window* getWindow()const;
    //Camera* getCamera()const;

    
    void setClearColor(glm::vec4 color);
    void setDrawWireFrame(bool flag);
    void setModelMatrix(glm::mat4 ma);
    void setViewportMatrix(glm::mat4 ma);
    void draw();

    void onUpdate();
    void onFrame();
    //void show();

private:

    bool isCtxOk();

    //std::unique_ptr<Window> m_window;
    std::unique_ptr<Camera>             m_camera;
    std::unique_ptr<Shader>             m_shader;
    std::unique_ptr<VertexInData>       m_vertex_in;
    std::unique_ptr<VertexOutData>      m_vertex_out;
    std::unique_ptr<FragmentInData>     m_fragment_in;
    std::unique_ptr<FragmentOutData>    m_fragment_out;
    std::shared_ptr<Framebuffer>        m_framebuffer;
    std::unique_ptr<Rasterizer>         m_rasterizer;
    std::unique_ptr<Scene>              m_scene;
    std::unique_ptr<RenderPassPhong>         m_renderpass;

    bool m_isDrawWireFrame;
    int m_Width, m_Height;
    glm::vec4 m_frameColor = {1.0f,1.0f,1.0f,1.0f};
    glm::vec4 m_clearColor;
    glm::mat4 m_modelMatrix;
    glm::mat4 m_viewportMatrix;



};

};
#endif