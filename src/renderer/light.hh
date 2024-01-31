#ifndef __LIGHT_H
#define __LLIGHT_H
#include "glm/glm.hpp"
#include <string>

namespace Yukiko{

class Light{
public:
    glm::vec3 _ambient;
    glm::vec3 _diffuse;
    glm::vec3 _specular;

};

class DirectionLight : public Light{
public:
    DirectionLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction);
    glm::vec3 _direction;
};

class PointLight : public Light{
public:
    PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position);
    void setLightPos(glm::vec3 position);
    glm::vec3 _position;
};

}

#endif //__LIGHT_H