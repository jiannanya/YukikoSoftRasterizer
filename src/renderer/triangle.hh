#ifndef __TRIANGLE_H
#define __TRIANGLE_H

#include "math.hh"

namespace Yukiko{

class Triangle{
public:
    Triangle();

    // vertex local pos
    glm::vec3 a();
    glm::vec3 b();
    glm::vec3 c();

    // vertex world pos
    glm::vec3 aw(); 
    glm::vec3 bw();
    glm::vec3 cw();

    // vertex viewport pos
    glm::vec3 avp(); 
    glm::vec3 bvp();
    glm::vec3 cvp();

    // texture coordinate
    glm::vec2 at();
    glm::vec2 bt();
    glm::vec2 ct();

    // normal local
    glm::vec3 an();
    glm::vec3 bn();
    glm::vec3 cn();

    // normal world
    glm::vec3 anw();
    glm::vec3 bnw();
    glm::vec3 cnw();    

    // color
    glm::vec4 ac();
    glm::vec4 bc();
    glm::vec4 cc();


    void setVertices(glm::vec3 ve[]);
    void setWorldVertices(glm::vec3 vw[]);
    void setViewPortVertices(glm::vec3 vp[]);
    void setTexCords(glm::vec2 vt[]);
    void setNormals(glm::vec3 vn[]);
    void setWorldNormals(glm::vec3 vnw[]);
    void setColors(glm::vec4 vc[]);

private:

    glm::vec3 _ve[3]; //vertex local coordinate
    glm::vec3 _vw[3]; //vertex world coordinate
    glm::vec3 _vp[3]; //vertex viewport coordinate
    glm::vec2 _vt[3]; //vertex texture coordinate
    glm::vec3 _vn[3]; //vertex normal
    glm::vec3 _vnw[3]; // vertex world normal
    glm::vec4 _vc[3]; //vertex color

};

}

#endif