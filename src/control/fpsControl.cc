#include "fpsControl.hh"

namespace Fallment{

FpsControls::FpsControls(std::shared_ptr<Camera> camera){
    m_camera = camera;
}


bool FpsControls::onInit(){

}
bool FpsControls::onUpdate(){

    while (!control_operation_queue.empty())
    {
        auto op = std::move(control_operation_queue.front());
        (*op)();
        control_operation_queue.pop();
    }
    


    return true;
}

void FpsControls::onDestory(){

}

void FpsControls::onEvent(const Event& e){

    //spdlog::debug("fps controls on event {}",static_cast<int>(e.m_Type));

    switch (e.m_Type)
    {
    case EventType::MousePos:
    {
        onMousePosEvent(e);
        break;
    }
    case EventType::MouseScroll:
    {
        onMouseScrollEvent(e);
        break;
    }
    case EventType::WindowSize:
    {
        onWindowSizeEvent(e);
        break;
    }

    case EventType::WindowClose:
    case EventType::None:
    {
        // currently do nothing
        break;
    }
        
    default:
        break;
    }
}

void FpsControls::onMousePosEvent(const Event& e){
    class MousePosOperation:public ControlOperation{
    public:
        MousePosOperation(const Camera& cam, double xpos, double ypos  )
        :m_cam{cam},m_xpos{xpos},m_ypos{ypos}{}
        void operator()() override{
            spdlog::debug("fps mouse pos operation");
        }
    private:
        const Camera& m_cam;
        double m_xpos;
        double m_ypos;
    };

    auto& ev = static_cast<MousePosEvent&>(const_cast<Event&>(e));
    if(m_camera.get()){
        this->control_operation_queue.emplace(std::make_unique<MousePosOperation>(*m_camera,ev.xpos,ev.ypos));
    }else{
        spdlog::error("fps control has no useful camera to use");
    }
}

void FpsControls::onMouseScrollEvent(const Event& e){
    class MouseScrollOperation:public ControlOperation{
    public:
        MouseScrollOperation(Camera& cam, double xoffset, double yoffset  ):
        m_cam{cam},m_xoffset{xoffset},m_yoffset{yoffset}{}
        void operator()() override{
            
            m_cam.m_Fovy -= mth::degreesToRadians((float)m_yoffset);
            if (m_cam.m_Fovy < mth::degreesToRadians(1.0f))
                m_cam.m_Fovy = mth::degreesToRadians(1.0f);
            if (m_cam.m_Fovy > mth::degreesToRadians(45.0f))
                m_cam.m_Fovy = mth::degreesToRadians(45.0f);

            //spdlog::debug("fps mouse scroll operation {} {} {}",m_xoffset , m_yoffset,m_cam.m_Fovy);
            m_cam.updateProjectionMatrix();
        }
    private:
        Camera& m_cam;
        double m_xoffset;
        double m_yoffset;
    };

    auto& ev = static_cast<MouseScrollEvent&>(const_cast<Event&>(e));
    if(m_camera.get()){
        //spdlog::info("fps camera ref count: {}",m_camera.use_count());
        this->control_operation_queue.emplace(std::make_unique<MouseScrollOperation>(*m_camera,ev.xoffset,ev.yoffset));
    }else{
        spdlog::error("fps control has no useful camera to use");
    }
}

void FpsControls::onWindowSizeEvent(const Event& e){
    class WindowSizeOperation:public ControlOperation{
    public:
        WindowSizeOperation(const Camera& cam, int width, int height  ):
        m_cam{cam},m_width{width},m_height{height}{}
        void operator()() override{
            
        }
    private:
        const Camera& m_cam;
        int m_width;
        int m_height;
    };

    auto& ev = static_cast<WindowSizeEvent&>(const_cast<Event&>(e));
    if(m_camera.get()){
        this->control_operation_queue.emplace(std::make_unique<WindowSizeOperation>(*m_camera,ev.width,ev.height));
    }else{
        spdlog::error("fps control has no useful camera to use");
    }
}

}