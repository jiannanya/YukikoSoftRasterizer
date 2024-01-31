
#include "triangle.hh"

namespace Yukiko{

Triangle::Triangle(){
    for(int k=0;k<3;k++){
        _ve[k] = _vn[k]  = {0.f,0.f,0.f};
        _vt[k] = {1.f,1.f};
        _vc[k] = {1.f,1.f,1.f,1.f};
    }
}

glm::vec3 Triangle::a(){
    return _ve[0];
}

glm::vec3 Triangle::b(){
    return _ve[1];
}

glm::vec3 Triangle::c(){
    return _ve[2];
}

glm::vec3 Triangle::aw(){
    return _vw[0];
}

glm::vec3 Triangle::bw(){
    return _vw[1];
}

glm::vec3 Triangle::cw(){
    return _vw[2];
}

glm::vec3 Triangle::avp(){
    return _vp[0];
}

glm::vec3 Triangle::bvp(){
    return _vp[1];
}

glm::vec3 Triangle::cvp(){
    return _vp[2];
}

glm::vec2 Triangle::at(){
    return _vt[0];
}
glm::vec2 Triangle::bt(){
    return _vt[1];
}
glm::vec2 Triangle::ct(){
    return _vt[2];
}

glm::vec3 Triangle::an(){
    return _vn[0];
}

glm::vec3 Triangle::bn(){
    return _vn[1];
}

glm::vec3 Triangle::cn(){
    return _vn[2];
}

glm::vec3 Triangle::anw(){
    return _vnw[0];
}

glm::vec3 Triangle::bnw(){
    return _vnw[1];
}

glm::vec3 Triangle::cnw(){
    return _vnw[2];
}


glm::vec4 Triangle::ac(){
    return _vc[0];
}

glm::vec4 Triangle::bc(){
    return _vc[1];
}

glm::vec4 Triangle::cc(){
    return _vc[2];
}

void Triangle::setVertices(glm::vec3 ve[]){
    _ve[0] = ve[0];
    _ve[1] = ve[1];
    _ve[2] = ve[2];
    
}

void Triangle::setWorldVertices(glm::vec3 vw[]){
    _vw[0] = vw[0];
    _vw[1] = vw[1];
    _vw[2] = vw[2];
}

void Triangle::setViewPortVertices(glm::vec3 vp[]){
    _vp[0] = vp[0];
    _vp[1] = vp[1];
    _vp[2] = vp[2];
}

void Triangle::setTexCords(glm::vec2 vt[]){
    _vt[0] = vt[0];
    _vt[1] = vt[1];
    _vt[2] = vt[2];
}

void Triangle::setNormals(glm::vec3 vn[]){
    _vn[0] = vn[0];
    _vn[1] = vn[1];
    _vn[2] = vn[2];
}

void Triangle::setWorldNormals(glm::vec3 vnw[]){
    _vnw[0] = vnw[0];
    _vnw[1] = vnw[1];
    _vnw[2] = vnw[2];
}

void Triangle::setColors(glm::vec4 vc[]){
    _vc[0] = vc[0];
    _vc[1] = vc[1];
    _vc[2] = vc[2];
}

}