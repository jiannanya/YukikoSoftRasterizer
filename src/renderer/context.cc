#include "context.hh"
#include "triangle.hh"

namespace Fallment{

Context::Context(){
    //m_window = nullptr;
    m_camera = nullptr;
    m_shader = nullptr;
    m_scene = nullptr;
    //m_framebuffer = nullptr;
    m_isDrawWireFrame = false;
    m_rasterizer = nullptr;   
}

Context::~Context(){}

// void Context::setWindow(window* window){
//     m_window = window;
// }

void Context::setCamera(std::shared_ptr<Camera> camera){
    m_camera = camera;
}

void Context::setShader(std::unique_ptr<Shader>&& shader){
    m_shader = std::move(shader);
}

void Context::setVertexShaderIn(std::unique_ptr<VertexInData>&& _data){
    m_vertex_in = std::move(_data);
}
void Context::setVertexShaderOut(std::unique_ptr<VertexOutData>&& _data){
    m_vertex_out = std::move(_data);
}
void Context::setFragmentShaderIn(std::unique_ptr<FragmentInData>&& _data){
    m_fragment_in = std::move(_data);
}
void Context::setFragmentShaderOut(std::unique_ptr<FragmentOutData>&& _data){
    m_fragment_out = std::move(_data);
}

void Context::setFrameBuffer(std::shared_ptr<Framebuffer>&& fb){
    m_framebuffer = fb;
    m_Width = fb->getWidth();
    m_Height = fb->getHeight();
}

// void Context::setTexture(texture* tex){
//     m_texture = tex;
// }

void Context::setScene(std::unique_ptr<Scene>&& sce){
    m_scene = std::move(sce);
}

void Context::setRasterizer(std::unique_ptr<Rasterizer>&& rast){
    m_rasterizer = std::move(rast);
}

// void Context::setRenderPass(std::unique_ptr<RenderPass> rp){
//     m_renderpass = std::move(rp);
// }

// framebuffer* Context::getFrameBuffer()const{
//     return m_framebuffer;
// }

// window* Context::getWindow()const{
//     return m_window;
// }

// camera* Context::getCamera()const{
//     return m_camera;
// }

void Context::setClearColor(glm::vec4 color){
    m_clearColor = color;
}

void Context::setModelMatrix(glm::mat4 ma){
    m_modelMatrix = ma;
}

void Context::setViewportMatrix(glm::mat4 ma){
    m_viewportMatrix = ma;
}

bool Context::isCtxOk(){
    return  m_framebuffer.get() && m_camera.get() && m_shader.get() && m_scene.get();
}

void Context::setDrawWireFrame(bool flag){
    m_isDrawWireFrame = flag;
}




void Context::draw(){

    if(!isCtxOk()){
        spdlog::error("Context not ok, drawing notthing");
        return;
    }

    // m_shader->setModel(m_modelMatrix);
    // m_shader->setView(m_camera->getViewMatrix());
    // m_shader->setPerspective(m_camera->getProjectionMatrix());


}

void Context::onUpdate(){

}
void Context::onFrame(){
    
}

// void Context::show(){
//     //m_window->drawBuffer();
// }

};