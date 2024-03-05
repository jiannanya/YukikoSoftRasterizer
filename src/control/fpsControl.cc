#include "fpsControl.hh"

namespace Fallment{

FpsControls::FpsControls(std::shared_ptr<Camera> camera){
    m_camera = camera;
}


bool FpsControls::onInit(){
    firstMouse = true;
    yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    pitch =  0.0f;
    lastX =  800.0f / 2.0f;
    lastY =  600.0f / 2.0f;
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
        MousePosOperation(Camera& cam, double xposIn, double yposIn, FpsControls* fpsControl)
        :m_cam{cam},m_xpos{xposIn},m_ypos{yposIn},fc{fpsControl}{}
        void operator()() override{
            //spdlog::debug("fps mouse pos operation");
            float xpos = static_cast<float>(m_xpos);
            float ypos = static_cast<float>(m_ypos);

            if (fc->firstMouse)
            {
                fc->lastX = xpos;
                fc->lastY = ypos;
                fc->firstMouse = false;
                return;
            }


            float turnSpeed = 0.1f;
            glm::vec3 frontoffset = getCameraFrontOffset(xpos,ypos);
            //spdlog::debug("fps mouse pos operation {} {} {}", frontoffset.x, frontoffset.y,frontoffset.z);

            m_cam.updateFront(m_cam.m_Front+frontoffset*turnSpeed);
            //m_cam.updateTarget(m_cam.m_Target+frontoffset*turnSpeed);


        }

    glm::vec3 getCameraFrontOffset(float xpos, float ypos) {

            float xoffset = xpos - fc->lastX;
            float yoffset = ypos - fc->lastY;
            fc->lastX = xpos;
            fc->lastY = ypos;

            glm::vec3 right = glm::cross(m_cam.m_Front, m_cam.m_UpDir);
            glm::vec3 realup = glm::cross(right,m_cam.m_Front);
            glm::vec3 xVec = -xoffset * right;
            //spdlog::debug("fps mouse pos operation {0} {1} {2} {3} {4} {5} {6} {7} {8}", right.x, right.y,right.z,m_cam.m_Front.x,m_cam.m_Front.y,m_cam.m_Front.z ,m_cam.m_UpWorld.x, m_cam.m_UpWorld.y,m_cam.m_UpWorld.z);
            glm::vec3 yVec = -yoffset * m_cam.m_UpDir;
            //spdlog::debug("fps mouse pos operation {0} {1} {2}",m_cam.m_UpDir.x,m_cam.m_UpDir.y,m_cam.m_UpDir.z);
            return glm::normalize(xVec+yVec);

    }
    
    virtual ~MousePosOperation(){}
    private:
        Camera& m_cam;
        double m_xpos;
        double m_ypos;
        FpsControls* fc;
    };

    auto& ev = static_cast<MousePosEvent&>(const_cast<Event&>(e));
    if(m_camera.get()){
        this->control_operation_queue.emplace(std::make_unique<MousePosOperation>(*m_camera,ev.xpos,ev.ypos,this));
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
    virtual ~MouseScrollOperation(){}
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
        virtual ~ WindowSizeOperation(){}
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