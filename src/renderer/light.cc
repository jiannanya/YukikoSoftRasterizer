//
// Created by lm on 2022/5/29.
//

#include "light.hh"

namespace Yukiko{

DirectionLight::DirectionLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction) {
    _ambient = ambient;
    _diffuse = diffuse;
    _specular = specular;
    _direction = direction;
}

PointLight::PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position) {
    _ambient = ambient;
    _diffuse = diffuse;
    _specular = specular;
    _position = position;
}

void PointLight::setLightPos(glm::vec3 position) {
    _position = position;
}

}