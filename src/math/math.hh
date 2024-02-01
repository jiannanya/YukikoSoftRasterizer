#ifndef __MATH_H
#define __MATH_H

#include "glm/glm.hpp"
#include <numbers>

namespace Yukiko::mth{

constexpr const float PI = std::numbers::pi;

inline float frac(float t) {
    float r = t - (int)t;
    if(r < 0.f)
        r = 1.0f - std::abs(r);

    return r;
}

inline float gamma(float x){
    return glm::pow(x,1.0/2.2);
}

//求反射向量
inline glm::vec3 reflect(const glm::vec3& I, const glm::vec3& N)
{
	//公式 R = I - 2(I·N)N
	return I - 2.f * glm::dot(I ,N) * N;
	 
}

template<typename T>
T clamp(T x, T min, T max) {
    return x < min ? min : (x > max ? max : x);
}

inline float square_distance(glm::vec3 p1, glm::vec3 p2) {
	return glm::length(p1-p2) * glm::length(p1-p2);
}

inline glm::vec3 barycentric3(glm::vec3& A, glm::vec3& B, glm::vec3& C, glm::vec3& p) {
    glm::vec3 xvec(C.x - A.x, B.x - A.x, A.x - p.x);
    glm::vec3 yvec(C.y - A.y, B.y - A.y, A.y - p.y);
    glm::vec3 u = glm::cross(xvec, yvec);
    if(std::abs(u.z) < 1e-2f)
        return glm::vec3(-1.0f, 1.0f, 1.0f); 

    return glm::vec3(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
}

inline glm::mat4 perspective(float fov, float aspect, float znear, float zfar) {
    float fax = 1.0f / (float)tan(fov * 0.5f);
    glm::mat4 ret = glm::mat4(1.0f);
    ret[0][0] = fax / aspect;
    ret[1][1] = fax;
    ret[2][2] = zfar / (zfar - znear);
    ret[3][2] = -znear * zfar / (zfar - znear);
    ret[2][3] = 1.f;
    return ret;
}

inline glm::mat4 lookat(glm::vec3 eye, glm::vec3 target, glm::vec3 worldup = glm::vec3(0,0,1)) {
    glm::mat4 ret = glm::mat4(1.0f);
    glm::vec3 forward = glm::normalize(eye - target);
    glm::vec3 left = glm::normalize(glm::cross(worldup,forward));
    glm::vec3 realup = glm::normalize(cross(forward,left));

    ret[0][0] = left.x;
    ret[1][0] = left.y;
    ret[2][0] = left.z;
    ret[0][1] = realup.x;
    ret[1][1] = realup.y;
    ret[2][1] = realup.z;
    ret[0][2] = forward.x;
    ret[1][2] = forward.y;
    ret[2][2] = forward.z;

    ret[0][3] = -left.x * eye.x - left.y * eye.y - left.z * eye.z;
    ret[1][3] = -realup.x * eye.x - realup.y * eye.y - realup.z * eye.z;
    ret[2][3] = -forward.x * eye.x - forward.y * eye.y - forward.z * eye.z;


    return ret;
}

glm::mat4 viewport(float _x, float _y,float _n, float _f, float width, float height) {
	glm::mat4 viewPortMatrix(1.0f);
	viewPortMatrix[0][0] = width/2.0f;
	viewPortMatrix[0][3] = _x + width/2.0f;
	viewPortMatrix[1][1] = height/2.0f;
	viewPortMatrix[1][3] = _y + height/2.0f;
	viewPortMatrix[2][2] = (_f - _n)/2.0f;
	viewPortMatrix[2][3] = (_f + _n)/2.0f;
	return viewPortMatrix;
}

inline glm::mat4 scale(glm::vec3 scalePara) {
	glm::mat4 trans = glm::mat4(1.0);
	for (int i = 0;i < 3;i++) {
		trans[i][i] *= scalePara[i];
	}
	return trans;
}

inline glm::mat4 translate(glm::vec3 translatePara) {
	glm::mat4 trans = glm::mat4(1.0);
	for (int i = 0;i < 3;i++) {
		trans[3][i] += translatePara[i];
	}
	return trans;
}


inline glm::mat4 rotate(glm::vec3 startPos, glm::vec3 direction, float angle) {

	float radians = (double)angle * PI / 180.0;
	glm::mat4 rotateM = glm::mat4(1.0);
	direction = glm::normalize(direction);
	float a = direction.x;
	float b = direction.y;
	float c = direction.z;
	rotateM[0][0] = a * a + (1 - a * a) * std::cos(radians);
	rotateM[0][1] = a * b * (1 - std::cos(radians)) - c * std::sin(radians);
	rotateM[0][2] = a * c * (1 - std::cos(radians)) + b * std::sin(radians);
	rotateM[1][0] = a * b * (1 - std::cos(radians)) + c * std::sin(radians);
	rotateM[1][1] = b * b + (1 - b * b) * std::cos(radians);
	rotateM[1][2] = b * c * (1 - std::cos(radians)) - a * std::sin(radians);
	rotateM[2][0] = a * c * (1 - std::cos(radians)) - b * std::sin(radians);
	rotateM[2][1] = b * c * (1 - std::cos(radians)) + a * std::sin(radians);
	rotateM[2][2] = c * c + (1 - c * c) * std::cos(radians);

	glm::vec3 trans = glm::vec3(-startPos.x, -startPos.y, -startPos.z);
	glm::mat4 forwardTrans = mth::translate(trans);
	glm::mat4 backTrans =  mth::translate(startPos);

    // 先平移到原点 ，然后绕过原点的任意轴旋转，最后平移回去 
	glm::mat4 rq = backTrans * rotateM * forwardTrans;

	return rq;
}

inline glm::mat4 rotate_z(float angle) {
	float radians = (double)angle * PI / 180.0;
	glm::mat4 rq = glm::mat4(1.0);
	rq[0][0] = std::cos(radians);
	rq[1][0] = 0 - std::sin(radians);
	rq[0][1] = std::sin(radians);
	rq[1][1] = std::cos(radians);
	return rq;
}

inline glm::mat4 rotate_y(float angle) {
	float radians = (double)angle * PI / 180.0;
	glm::mat4 rq = glm::mat4(1.0);
	rq[0][0] = std::cos(radians);
	rq[0][2] = 0 - std::sin(radians);
	rq[2][0] = std::sin(radians);
	rq[2][2] = std::cos(radians);
	return rq;
}

inline glm::mat4 rotate_x(float angle) {
	float radians = (double)angle * PI / 180.0;
	glm::mat4 rq = glm::mat4(1.0);
	rq[1][1] = std::cos(radians);
	rq[2][1] = 0 - std::sin(radians);
	rq[1][2] = std::sin(radians);
	rq[2][2] = std::cos(radians);
	return rq;
}


}


#endif