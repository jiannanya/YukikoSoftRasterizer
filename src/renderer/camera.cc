#include "camera.hh"
#include "math.hh"

#include "spdlog/spdlog.h"

namespace Fallment{

Camera::Camera(float fovy, float aspect,glm::vec3 position, glm::vec3 target, glm::vec3 upDir)
    :m_Fovy(fovy)
    ,m_Aspect(aspect) 
    ,m_Position(position)
    ,m_Target(target)
    ,m_UpDir(upDir)
{       
        m_ViewMatrix = glm::mat4(1.0f);
        m_ProjectionMatrix = glm::mat4(1.0f);
        updateViewMatrix();
        updateProjectionMatrix(); 
};

void Camera::updateAttitude(glm::vec3 position, glm::vec3 target, glm::vec3 upDir) {
    m_Position = position;
    m_Target = target;
    m_UpDir = upDir;
    updateViewMatrix();
}


void Camera::updatePosition(glm::vec3 position) {
    //std::cout<<"update Camera pos: "<<position.x<<", "<<position.y<<", "<<position.z<<std::endl;
    m_Position = position;
    updateViewMatrix();
}


void Camera::updateViewMatrix() {
    spdlog::debug("update Camera ViewMatrix");
    m_ViewMatrix = mth::lookat(m_Position, m_Target, m_UpDir);
    updateViewProjectionMatrix();
}

void Camera::updateProjectionMatrix() {
    spdlog::debug("update Camera ProjectionMatrix");
    m_ProjectionMatrix = mth::perspective(m_Fovy, m_Aspect, 0.1f, 10000.0f);
    updateViewProjectionMatrix();
}

void Camera::updateViewProjectionMatrix() {
    spdlog::debug("update Camera ViewProjectionMatrix");
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

glm::mat4 Camera::getViewMatrix(){
    return m_ViewMatrix;
}

glm::mat4 Camera::getProjectionMatrix(){
    return m_ProjectionMatrix;
}

glm::vec3 Camera::getPos(){
    return m_Position;
}

glm::vec3 Camera::getTarget(){
    return m_Target;
}

glm::vec3 Camera::getUp(){
    return m_UpDir;
}

};