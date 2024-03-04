#include "fpsControl.hh"

namespace Fallment{

FpsControls::FpsControls(std::unique_ptr<Camera>&& camera){
    m_camera = std::move(camera);
}


bool FpsControls::onInit(){

}
bool FpsControls::onUpdate(){

    while (!control_operation_queue.empty())
    {
        spdlog::debug("fps control on update 2");
        auto op = std::move(control_operation_queue.front());
        (*op)();
        control_operation_queue.pop();
    }
    


    return true;
}

void FpsControls::onDestory(){

}

void FpsControls::onEvent(const Event& e){

    spdlog::debug("fps controls on event");

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
    }
}

void FpsControls::onMouseScrollEvent(const Event& e){
    class MouseScrollOperation:public ControlOperation{
    public:
        MouseScrollOperation(const Camera& cam, double xoffset, double yoffset  ):
        m_cam{cam},m_xoffset{xoffset},m_yoffset{yoffset}{}
        void operator()() override{
            
        }
    private:
        const Camera& m_cam;
        double m_xoffset;
        double m_yoffset;
    };

    auto& ev = static_cast<MouseScrollEvent&>(const_cast<Event&>(e));
    if(m_camera.get()){
        this->control_operation_queue.emplace(std::make_unique<MouseScrollOperation>(*m_camera,ev.xoffset,ev.yoffset));
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
    }
}

}