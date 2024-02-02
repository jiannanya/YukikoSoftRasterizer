#ifndef __MATERIAL_H
#define __MATERIAL_H

#include "glm/glm.hpp"

namespace Fallment{

struct Material{
    glm::vec3 ka;
    glm::vec3 kd;
    glm::vec3 ks;
    float shininess;
    // default initialize
    Material(){
        ka = glm::vec3(0.2f,0.2f,0.2f);
        kd= glm::vec3(1.0f,0.5f,0.5f);
        ks = glm::vec3(0.2f,0.2f,0.2f);
        shininess = 16.0f;
    }
    Material(glm::vec3 _ka, glm::vec3 _kd, glm::vec3 _ks, float _shininess){
        ka = _ka;
        kd = _kd;
        ks = _ks;
        shininess = _shininess;
}

};

}

#endif

