#include "appSSAO.hh"


namespace Fallment{

const char *TITLE = "Fallment real time soft render";
const char *OBJ_PATH = "C:\\CC\\src\\sandbox\\FallmentSoftRasterizer\\build\\case\\assert\\african_head0.obj";
const char *OBJ_TEXTURE_PATH =  "C:\\CC\\src\\sandbox\\FallmentSoftRasterizer\\build\\case\\assert\\african_head_diffuse.tga";

constexpr int WINDOW_WIDTH = 500;
constexpr int WINDOW_HEIGHT = 500;
constexpr float FOV_INIT = mth::PI/4.0f;

glm::vec3 CAM_POS_INIT = glm::vec3(0, 0, 3);
glm::vec3 CAM_TARGET_INIT = glm::vec3(0,0,0);
glm::vec3 CAM_UP_INIT = glm::vec3(0,1,0);

AppSSAO::AppSSAO(){

}

AppSSAO::~AppSSAO(){

}

bool AppSSAO::onInit(){
    spdlog::set_level(spdlog::level::debug);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v"); //%Y-%m-%d %H:%M:%S 代表日期和时间。 %l 代表日志级别。%v 代表实际的日志消息文本。
    //spdlog::set_formatter


    spdlog::info("App start init");
    auto  ctx_framebuffer = std::make_shared<Framebuffer>(WINDOW_WIDTH,WINDOW_HEIGHT);

    if(!ctx_framebuffer.get()){
        spdlog::error("Apps framebuffer are not useful on init !");
        return false;
    }

    m_window = std::make_unique<Window>(TITLE, WINDOW_WIDTH,WINDOW_HEIGHT);
    if(!m_window->onInit()){
        spdlog::error("Apps window are not useful on init !");
        return false;
    }
    m_window->setFramebuffer(ctx_framebuffer);
    auto  ctx_camera = std::make_shared<Camera>(FOV_INIT, float(WINDOW_WIDTH) / float(WINDOW_HEIGHT),CAM_POS_INIT, CAM_TARGET_INIT,CAM_UP_INIT);
    m_controls = std::make_unique<FpsControls>(ctx_camera);

    auto  ctx_model1 = std::make_unique<Mesh>(OBJ_PATH);

    if(!ctx_model1.get()){
        spdlog::error("Apps mesh model are not useful on init !");
        return false;
    }
    auto  ctx_texture = std::make_unique<Texture>(std::string(OBJ_TEXTURE_PATH));
    
    auto  ctx_model_matrix = glm::mat4{1.0f};

    auto  ctx_shader = std::make_unique<SSAOShader>();
    auto  ctx_SSAOShaderVertexIn = std::make_unique<VertexInDataSSAO>(
        ctx_model_matrix,
        ctx_camera->getViewMatrix(),
        ctx_camera->getProjectionMatrix()
        //mth::orthographic(-2.0f,2.0f,-2.0f,2.0f,0.1f,3.0f)
    );
    auto  ctx_SSAOShaderVertexOut = std::make_unique<VertexOutDataSSAO>();
    auto ctx_SSAOShaderFragmentIn = std::make_unique<FragmentInDataSSAO>();
    auto ctx_SSAOShaderFragmentOut = std::make_unique<FragmentOutDataSSAO>();

    ctx_shader->_vertexIn = std::move(ctx_SSAOShaderVertexIn);
    ctx_shader->_vertexOut = std::move(ctx_SSAOShaderVertexOut);
    ctx_shader->_fragmentIn = std::move(ctx_SSAOShaderFragmentIn);
    ctx_shader->_fragmentOut = std::move(ctx_SSAOShaderFragmentOut);

    if(!ctx_shader.get()){
        spdlog::error("Apps shader are not useful on init !");
        return false;
    }

    auto ctx_scene = std::make_unique<Scene>();
    ctx_scene->addMesh(std::move(ctx_model1));

    if(!ctx_scene.get()){
       spdlog::error("Apps scene are not useful on init !");
        return false;
    }

    m_ctx = std::make_shared<Context>();
    m_ctx->setFrameBuffer(ctx_framebuffer);

    m_ctx->setCamera(ctx_camera);
    m_ctx->setScene(std::move(ctx_scene));

    m_ctx->setShader(std::move(ctx_shader));
    m_ctx->setDrawWireFrame(false);
    m_ctx->setClearColor(glm::vec4(0.0f,0.0f,0.0f,1.0f));
    m_ctx->setModelMatrix(ctx_model_matrix);
    m_ctx->setViewportMatrix(mth::viewport(0,0,1,0,WINDOW_WIDTH,WINDOW_HEIGHT));
    m_ctx->setRasterizer(std::move(std::make_unique<RasterizerSSAO>()));

    if(m_window->getEventDispatcher()){
        //should recreate window and framebuffer size
        auto viewport_et = std::make_unique<EventCallbackFnType>(std::bind(
        [this](const Event& e){
            if(e.m_Type==EventType::WindowSize){
                auto& ev = static_cast<WindowSizeEvent&>(const_cast<Event&>(e));
                this->m_ctx->getFrameBuffer()->recreate(ev.width,ev.height);
                this->m_window->recreate(TITLE,ev.width,ev.height);
                //spdlog::debug("WindowSizeEvent {} {}",ev.width,ev.height);
                auto cam = this->m_ctx->getCamera();
                cam->m_Aspect = static_cast<float>(ev.width)/static_cast<float>(ev.height);
                cam->updateProjectionMatrix();
                this->m_ctx->setViewportMatrix(mth::viewport(0,0,1,0,ev.width,ev.height));

                this->onUpdate();
                this->onFrame();
            }
            
        },std::placeholders::_1));
        m_window->getEventDispatcher()->addEventCallback(*viewport_et);
        m_ecft.emplace_back(std::move(viewport_et));

    }else{
        spdlog::error("window does not has event dispatcher");
    }
    


    if(!m_ctx.get()){
        spdlog::error("Apps context are not useful on init !");
        return false;
    }

    m_renderpass = std::make_unique<RenderPassSSAO>();
    m_renderpass->setContext(m_ctx);

    if(!m_renderpass.get()){
       spdlog::error("Apps context are not useful on init !");
       return false;
    }
    spdlog::info("init ok");
    return true;
}
bool AppSSAO::onUpdate(){
    //spdlog::debug("on update");

    if(m_window.get()){
        if(!m_window->onUpdate())return false;
    }else{
        spdlog::error("Apps window does not useful! on update");
        return false;
    }

    if(m_controls.get()){
        m_controls->onUpdate();
    }

    if(m_ctx.get()&&m_renderpass.get()){
        m_ctx->onUpdate();
        m_renderpass->onUpdate();
        
    }else{
        spdlog::error("Apps context,window and renderpass do not useful! on update");
        return false;
    }
    

    return true;
    
    
}

void AppSSAO::onFrame(){
    if(m_window.get()&&m_renderpass.get()){
        m_renderpass->onFrame();
        m_window->onFrame();
    }else{
        spdlog::error("Apps window and renderpass are not useful! on frame");
    }

}

void AppSSAO::onDestory(){

}

void AppSSAO::run(){
    spdlog::info("App start run");
    while(onUpdate()){
        onFrame();
    }
}

}