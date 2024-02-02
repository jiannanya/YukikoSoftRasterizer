#ifndef CAMERA_HH
#define CAMERA_HH

#include "math.hh"

namespace Fallment{

class Camera {
public:

    glm::vec3 m_Position;
    glm::vec3 m_Target;
    glm::vec3 m_UpDir;

    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewProjectionMatrix;

    float m_Fovy;
    float m_Aspect;

    Camera(){}
    Camera(float fovy, float aspect,glm::vec3 position, glm::vec3 target, glm::vec3 upDir=glm::vec3(0,1,0));

    void updateAttitude(glm::vec3 position, glm::vec3 target, glm::vec3 upDir=glm::vec3(0,1,0));

    void updatePosition(glm::vec3 position);

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    glm::vec3 getPos();
    glm::vec3 getTarget();
    glm::vec3 getUp();

private:
    void updateViewMatrix();
    void updateProjectionMatrix();
    void updateViewProjectionMatrix();
};

};

#endif