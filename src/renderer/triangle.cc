
#include "triangle.hh"

namespace Fallment{


glm::vec3& Triangle::a(){
    return _ve[0];
}

glm::vec3& Triangle::b(){
    return _ve[1];
}

glm::vec3& Triangle::c(){
    return _ve[2];
}

glm::vec3& Triangle::av(){
    return _vv[0];
}

glm::vec3& Triangle::bv(){
    return _vv[1];
}

glm::vec3& Triangle::cv(){
    return _vv[2];
}

glm::vec3& Triangle::aw(){
    return _vw[0];
}

glm::vec3& Triangle::bw(){
    return _vw[1];
}

glm::vec3& Triangle::cw(){
    return _vw[2];
}

glm::vec3& Triangle::avp(){
    return _vp[0];
}

glm::vec3& Triangle::bvp(){
    return _vp[1];
}

glm::vec3& Triangle::cvp(){
    return _vp[2];
}

glm::vec2& Triangle::auv(){
    return _vuv[0];
}
glm::vec2& Triangle::buv(){
    return _vuv[1];
}
glm::vec2& Triangle::cuv(){
    return _vuv[2];
}

glm::vec3& Triangle::an(){
    return _vn[0];
}

glm::vec3& Triangle::bn(){
    return _vn[1];
}

glm::vec3& Triangle::cn(){
    return _vn[2];
}

glm::vec3& Triangle::anw(){
    return _vnw[0];
}

glm::vec3& Triangle::bnw(){
    return _vnw[1];
}

glm::vec3& Triangle::cnw(){
    return _vnw[2];
}


glm::vec4& Triangle::aco(){
    return _vco[0];
}

glm::vec4& Triangle::bco(){
    return _vco[1];
}

glm::vec4& Triangle::cco(){
    return _vco[2];
}


}