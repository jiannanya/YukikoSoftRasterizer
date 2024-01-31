#include "appMain.hh"


namespace Yukiko{

AppMain::AppMain(){
    onInit();
}

AppMain::~AppMain(){
    onDestory();
}

void AppMain::onInit(){
    
    auto  ctx_framebuffer = std::make_unique<Framebuffer>(WINDOW_WIDTH,WINDOW_HEIGHT);
    auto  ctx_window = std::make_unique<Window>(TITLE, WINDOW_WIDTH,WINDOW_HEIGHT);
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

    auto ctx_PhongShaderFragmentIn = std::make_unique<FragmentIndataPhong>();

    ctx_PhongShaderFragmentIn->pointLights.emplace_back(std::move(p_light1));
    ctx_PhongShaderFragmentIn->pointLights.emplace_back(std::move(p_light2));

    auto ctx_scene = std::make_unique<Scene>();
    ctx_scene->addMesh(std::move(ctx_model1));

    auto _Ctx = std::make_unique<Context>();
   //auto_context = context();
    _Ctx->setFrameBuffer(std::move(ctx_framebuffer));
    //_Ctx->setWindow(&ms_window);
    _Ctx->setCamera(std::move(ctx_camera));
    _Ctx->setScene(std::move(ctx_scene));
    //_Ctx->setTexture(&ms_texture);
    _Ctx->setShader(std::move(ctx_shader));
    _Ctx->setDrawWireFrame(false);
    _Ctx->setClearColor(glm::vec4(0.0f,0.0f,0.0f,1.0f));
    _Ctx->setModelMatrix(ctx_model_matrix);

    // renderer ms_render =  renderer(ms_context);
    // ms_render.render();
    m_renderpass = std::make_unique<RenderPass>(std::move(_Ctx));
}
void AppMain::onUpdate(){

}

void AppMain::onFrame(){

}

void AppMain::onDestory(){

}

void AppMain::run(){
    
}

}