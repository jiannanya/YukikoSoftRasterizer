#include "appLine.hh"


namespace Fallment{

const char *TITLE = "Fallment real time soft render";
const char *OBJ_PATH = "C:\\CC\\src\\sandbox\\FallmentSoftRasterizer\\build\\case\\assert\\african_head0.obj";
//const char *OBJ_TEXTURE_PATH =  "C:\\CC\\src\\sandbox\\FallmentSoftRasterizer\\build\\case\\assert\\african_head_diffuse.tga";

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr float FOV_INIT = mth::PI/4.0f;

glm::vec3 CAM_POS_INIT = glm::vec3(0, 0, 3);
glm::vec3 CAM_TARGET_INIT = glm::vec3(0,0,0);
glm::vec3 CAM_UP_INIT = glm::vec3(0,1,0);

AppLine::AppLine(){

}

AppLine::~AppLine(){

}

bool AppLine::onInit(){
    spdlog::set_level(spdlog::level::debug);
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



    auto  ctx_model1 = std::make_unique<Mesh>(OBJ_PATH);

    if(!ctx_model1.get()){
        spdlog::error("Apps mesh model are not useful on init !");
        return false;
    }
    //auto  ctx_texture = std::make_unique<Texture>(std::string(OBJ_TEXTURE_PATH));
    auto  ctx_camera = std::make_unique<Camera>(FOV_INIT, float(WINDOW_WIDTH) / float(WINDOW_HEIGHT),CAM_POS_INIT, CAM_TARGET_INIT,CAM_UP_INIT);
    auto  ctx_model_matrix = glm::translate(glm::mat4{1.0f},glm::vec3(0,0,0));

    
    auto  ctx_shader = std::make_unique<TransformShader>();
    auto  ctx_TransformShaderVertexIn = std::make_unique<VertexInDataTransform>(
        ctx_model_matrix,
        ctx_camera->getViewMatrix(),
        ctx_camera->getProjectionMatrix()
        //mth::orthographic(-2.0f,2.0f,-2.0f,2.0f,0.1f,3.0f)
    );
    auto  ctx_TransformShaderVertexOut = std::make_unique<VertexOutDataTransform>();
    auto ctx_TransformShaderFragmentIn = std::make_unique<FragmentInDataTransform>();
    auto ctx_TransformShaderFragmentOut = std::make_unique<FragmentOutDataTransform>();

    ctx_shader->_vertexIn = std::move(ctx_TransformShaderVertexIn);
    ctx_shader->_vertexOut = std::move(ctx_TransformShaderVertexOut);
    ctx_shader->_fragmentIn = std::move(ctx_TransformShaderFragmentIn);
    ctx_shader->_fragmentOut = std::move(ctx_TransformShaderFragmentOut);

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
    m_ctx->setFrameBuffer(std::move(ctx_framebuffer));

    m_ctx->setCamera(std::move(ctx_camera));
    m_ctx->setScene(std::move(ctx_scene));

    m_ctx->setShader(std::move(ctx_shader));
    m_ctx->setDrawWireFrame(false);
    m_ctx->setClearColor(glm::vec4(0.0f,0.0f,0.0f,1.0f));
    m_ctx->setModelMatrix(ctx_model_matrix);
    m_ctx->setViewportMatrix(mth::viewport(0,0,0,1,WINDOW_WIDTH,WINDOW_HEIGHT));
    m_ctx->setRasterizer(std::move(std::unique_ptr<Rasterizer>(new RasterizerLine)));

    if(!m_ctx.get()){
        spdlog::error("Apps context are not useful on init !");
        return false;
    }

    m_renderpass = std::unique_ptr<RenderPassLine>(new RenderPassLine);
    m_renderpass->setContext(m_ctx);

    if(!m_renderpass.get()){
        spdlog::error("Apps context are not useful on init !");
        return false;
    }
    spdlog::info("init ok");
    return true;
}
bool AppLine::onUpdate(){
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

void AppLine::onFrame(){
    //spdlog::debug("on frame");
    if(m_window.get()&&m_renderpass.get()){
        m_renderpass->onFrame();
        m_window->onFrame();
    }else{
        spdlog::error("Apps window and renderpass are not useful! on frame");
    }

}

void AppLine::onDestory(){

}

void AppLine::run(){
    spdlog::info("App start run");
    while(onUpdate()){
        onFrame();
    }
}

}