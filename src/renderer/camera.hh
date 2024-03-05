#ifndef CAMERA_HH
#define CAMERA_HH

#include "math/math.hh"

namespace Fallment{

class Camera {
public:

    glm::vec3 m_Position;
    glm::vec3 m_Target;
    glm::vec3 m_UpDir;
    glm::vec3 m_Front;

    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewProjectionMatrix;

    float m_Fovy;
    float m_Aspect;

    Camera(){}
    Camera(float fovy, float aspect,glm::vec3 position, glm::vec3 target, glm::vec3 upDir=glm::vec3(0,1,0));

    void updateAttitude(glm::vec3 position, glm::vec3 target, glm::vec3 upDir=glm::vec3(0,1,0));

    void updatePosition(glm::vec3 position);
    void updateTarget(glm::vec3 tar);
    void updateFront(glm::vec3 front);

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    glm::vec3 getPos();
    glm::vec3 getTarget();
    glm::vec3 getUp();

public:
    void updateViewMatrix();
    void updateProjectionMatrix();
    void updateViewProjectionMatrix();
};

class OrthographicCam:public Camera{
public:
    OrthographicCam(float left,float right,float bottom,float top,float znear,float zfar)
    :m_left{left},m_right{right},m_bottom{bottom},m_top{top},m_znear{znear},m_zfar{zfar}{

    }


private:

    float m_left;
    float m_right;
    float m_bottom;
    float m_top;
    float m_znear;
    float m_zfar;

};

};

#endif