#include "appPhong.hh"


namespace Fallment{

AppPhong::AppPhong(){

}

AppPhong::~AppPhong(){

}

bool AppPhong::onInit(){
    
    auto  ctx_framebuffer = std::make_shared<Framebuffer>(WINDOW_WIDTH,WINDOW_HEIGHT);
    m_window = std::make_unique<Window>(TITLE, WINDOW_WIDTH,WINDOW_HEIGHT);
    m_window->setFramebuffer(ctx_framebuffer);


    auto  ctx_model1 = std::make_unique<Mesh>(OBJ_PATH);
    auto  ctx_texture = std::make_unique<Texture>(std::string(OBJ_TEXTURE_PATH));
    auto  ctx_camera = std::make_unique<Camera>(FOV_INIT, float(WINDOW_WIDTH) / WINDOW_HEIGHT,CAM_POS_INIT, CAM_TARGET_INIT,CAM_UP_INIT);
    auto  ctx_model_matrix = glm::mat4{1.0f};
    auto  ctx_shader = std::make_unique<PhongShader>();
    auto  ctx_PhongShaderVertexIn = std::make_unique<VertexInDataPhong>(
        ctx_model_matrix,
        ctx_camera->getViewMatrix(),
        ctx_camera->getProjectionMatrix(),
        ctx_camera->getPos()
    );

    auto  ctx_PhongShaderVertexOut = std::make_unique<VertexOutDataPhong>();
    // ms_shader.setModel();
    // ms_shader.setView(ms_camera.getViewMatrix());
    // ms_shader.setPerspective(ms_camera.getProjectionMatrix());
    // ms_shader.setDiffuseTexture(&ms_texture);

    auto p_light1 = std::make_unique<PointLight>(   glm::vec3(0.2f,0.2f,0.2f),
                                                    glm::vec3(0.5f,0.5f,0.5f),
                                                    glm::vec3(1.0f,1.0f,1.0f),
                                                    glm::vec3(0, 20, 0)
                                                );

    auto p_light2 = std::make_unique<PointLight>(   glm::vec3(0.2f,0.2f,0.2f),
                                                    glm::vec3(0.5f,0.5f,0.5f),
                                                    glm::vec3(1.0f,1.0f,1.0f),
                                                    glm::vec3(20, 0, 0)
                                    );

    auto ctx_PhongShaderFragmentIn = std::make_unique<FragmentInDataPhong>();

    ctx_PhongShaderFragmentIn->pointLights.emplace_back(std::move(p_light1));
    ctx_PhongShaderFragmentIn->pointLights.emplace_back(std::move(p_light2));

    auto ctx_PhongShaderFragmentOut = std::make_unique<FragmentOutDataPhong>();

    ctx_shader->_vertexIn = std::move(ctx_PhongShaderVertexIn);
    ctx_shader->_vertexOut = std::move(ctx_PhongShaderVertexOut);
    ctx_shader->_fragmentIn = std::move(ctx_PhongShaderFragmentIn);
    ctx_shader->_fragmentOut = std::move(ctx_PhongShaderFragmentOut);

    auto ctx_scene = std::make_unique<Scene>();
    ctx_scene->addMesh(std::move(ctx_model1));

    m_ctx = std::make_shared<Context>();
    m_ctx->setFrameBuffer(ctx_framebuffer);
    //_Ctx->setWindow(&ms_window);
    m_ctx->setCamera(std::move(ctx_camera));
    m_ctx->setScene(std::move(ctx_scene));
    //_Ctx->setTexture(&ms_texture);
    m_ctx->setShader(std::move(ctx_shader));
    m_ctx->setDrawWireFrame(false);
    m_ctx->setClearColor(glm::vec4(0.0f,0.0f,0.0f,1.0f));
    m_ctx->setModelMatrix(ctx_model_matrix);
    m_ctx->setViewportMatrix(mth::viewport(0,0,0,1,WINDOW_WIDTH,WINDOW_HEIGHT));
    m_ctx->setRasterizer(std::move(std::make_unique<RasterizerPhong>()));

    // renderer ms_render =  renderer(ms_context);
    // ms_render.render();
    m_renderpass = std::make_unique<RenderPass>();
    m_renderpass->setContext(m_ctx);


    return true;
}
bool AppPhong::onUpdate(){
    if(m_controls.get()){
        m_controls->onUpdate();
    }
    if(m_ctx.get()&&m_renderpass.get()){
        m_ctx->onUpdate();
        m_renderpass->onUpdate();
    }else{
        spdlog::error("Apps context and renderpass are not useful!");
        return false;
    }
    
    
}

void AppPhong::onFrame(){
    m_renderpass->onFrame();
}

void AppPhong::onDestory(){

}

void AppPhong::run(){
    while(onUpdate()){
        onFrame();
    }
}

}