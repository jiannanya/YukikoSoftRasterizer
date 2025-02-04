#ifndef __MATH_H
#define __MATH_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <numbers>

namespace Fallment::mth {

constexpr const float PI = std::numbers::pi;

inline float degreesToRadians(float angle) { return angle * PI / 180.0f; }
inline float radiansToDegrees(float angle) { return angle * 180.0f / PI; }

inline float frac(float t) {
    float r = t - (int)t;
    if (r < 0.f)
        r = 1.0f - std::abs(r);

    return r;
}

inline float gamma(float x) { return glm::pow(x, 1.0 / 2.2); }

// 求反射向量
inline glm::vec3 reflect(const glm::vec3& I, const glm::vec3& N) {
    // 公式 R = I - 2(I·N)N
    return I - 2.f * glm::dot(I, N) * N;
}

template <typename T> T clamp(T x, T min, T max) {
    return x < min ? min : (x > max ? max : x);
}

inline float square_distance(glm::vec3 p1, glm::vec3 p2) {
    return glm::length(p1 - p2) * glm::length(p1 - p2);
}

inline glm::vec3 barycentric3(glm::vec3& A, glm::vec3& B, glm::vec3& C,
                              glm::vec3& p) {
    glm::vec3 xvec(C.x - A.x, B.x - A.x, A.x - p.x);
    glm::vec3 yvec(C.y - A.y, B.y - A.y, A.y - p.y);
    glm::vec3 u = glm::cross(xvec, yvec);
    if (std::abs(u.z) < 1e-2f)
        return glm::vec3(-1.0f, 1.0f, 1.0f);

    return glm::vec3(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
}

inline glm::vec3 barycentric2D(glm::vec3& A, glm::vec3& B, glm::vec3& C,
                               glm::vec3& p) {

    float x = p.x, y = p.y;
    float x1 = A.x, y1 = A.y;
    float x2 = B.x, y2 = B.y;
    float x3 = C.x, y3 = C.y;
    float a = (x * (y2 - y3) + (x3 - x2) * y + x2 * y3 - x3 * y2) /
              (x1 * (y2 - y3) + (x3 - x2) * y1 + x2 * y3 - x3 * y2);
    float b = (x * (y3 - y1) + (x1 - x3) * y + x3 * y1 - x1 * y3) /
              (x2 * (y3 - y1) + (x1 - x3) * y2 + x3 * y1 - x1 * y3);
    float c = (x * (y1 - y2) + (x2 - x1) * y + x1 * y2 - x2 * y1) /
              (x3 * (y1 - y2) + (x2 - x1) * y3 + x1 * y2 - x2 * y1);
    return {a, b, c};
}

inline glm::vec3 barycentric2D2(glm::vec3& A, glm::vec3& B, glm::vec3& C,
                                glm::vec3& p) {

    float x = p.x, y = p.y;
    float x0 = A.x, y0 = A.y;
    float x1 = B.x, y1 = B.y;
    float x2 = C.x, y2 = C.y;
    float a = ((x - x2) * (y1 - y2) - ((x1 - x2) * (y - y2))) /
              ((x0 - x2) * (y1 - y2) - (x1 - x2) * (y0 - y2));
    float b = ((x0 - x2) * (y - y2) - (x - x2) * (y0 - y2)) /
              ((x0 - x2) * (y1 - y2) - (x1 - x2) * (y0 - y2));
    float c = 1 - a - b;
    return {a, b, c};
}

// barycentric interpolate with perspective correction
inline glm::vec2 interpolate(glm::vec2 a, glm::vec2 b, glm::vec2 c,
                             glm::vec3 bc, float z1, float z2, float z3,
                             float z_reciprocal) {
    glm::vec2 res;
    res.x = (bc.x * (a.x / z1) + bc.y * (b.x / z2) + bc.z * (c.x / z3)) /
            z_reciprocal;
    res.y = (bc.x * (a.y / z1) + bc.y * (b.y / z2) + bc.z * (c.y / z3)) /
            z_reciprocal;
    return res;
}

inline glm::vec3 interpolate(glm::vec3 a, glm::vec3 b, glm::vec3 c,
                             glm::vec3 bc, float z1, float z2, float z3,
                             float z_reciprocal) {
    glm::vec3 res;
    res.x = (bc.x * (a.x / z1) + bc.y * (b.x / z2) + bc.z * (c.x / z3)) /
            z_reciprocal;
    res.y = (bc.x * (a.y / z1) + bc.y * (b.y / z2) + bc.z * (c.y / z3)) /
            z_reciprocal;
    res.z = (bc.x * (a.z / z1) + bc.y * (b.z / z2) + bc.z * (c.z / z3)) /
            z_reciprocal;
    return res;
}

inline glm::vec4 interpolate(glm::vec4 a, glm::vec4 b, glm::vec4 c,
                             glm::vec3 bc, float z1, float z2, float z3,
                             float z_reciprocal) {
    glm::vec4 res;
    res.x = (bc.x * (a.x / z1) + bc.y * (b.x / z2) + bc.z * (c.x / z3)) /
            z_reciprocal;
    res.y = (bc.x * (a.y / z1) + bc.y * (b.y / z2) + bc.z * (c.y / z3)) /
            z_reciprocal;
    res.z = (bc.x * (a.z / z1) + bc.y * (b.z / z2) + bc.z * (c.z / z3)) /
            z_reciprocal;
    res.w = (bc.x * (a.w / z1) + bc.y * (b.w / z2) + bc.z * (c.w / z3)) /
            z_reciprocal;
    return res;
}

inline glm::mat4 perspective(float fov, float aspect, float znear, float zfar) {
    glm::mat4 ret{1.0f};
    float f = (float)std::tan(fov * 0.5f);
    ret[0][0] = 1.0f / (f * aspect);
    ret[1][1] = 1.0f / f;
    ret[2][2] = -(znear + zfar) / (zfar - znear);
    ret[2][3] = -1.0f;
    ret[3][2] = -(2.0f * znear * zfar) / (zfar - znear);
    // ret = glm::perspective(fov,aspect,znear,zfar);
    return ret;
}

inline glm::mat4 orthographic(float left, float right, float bottom, float top,
                              float znear, float zfar) {
    glm::mat4 ret{1.0f};
    ret[0][0] = 2.0f / (right - left);
    ret[1][1] = 2.0f / (top - bottom);
    ret[2][2] = 2.0f / (znear - zfar);
    ret[3][0] = -(right + left) / (right - left);
    ret[3][1] = -(top + bottom) / (top - bottom);
    ret[3][2] = -(znear + zfar) / (znear - zfar);

    return ret;
}

inline glm::mat4 lookat(glm::vec3 camera, glm::vec3 target,
                        glm::vec3 up = glm::vec3(0, 1, 0)) {

    glm::vec3 n = glm::normalize(camera - target);   // -forward
    glm::vec3 u = glm::normalize(glm::cross(n, up)); // right
    glm::vec3 v = glm::normalize(glm::cross(u, n));  // real up

    glm::mat4 viewMatrix{1.0f};

    viewMatrix[0][0] = u.x;
    viewMatrix[1][0] = u.y;
    viewMatrix[2][0] = u.z;
    viewMatrix[0][1] = v.x;
    viewMatrix[1][1] = v.y;
    viewMatrix[2][1] = v.z;
    viewMatrix[0][2] = n.x;
    viewMatrix[1][2] = n.y;
    viewMatrix[2][2] = n.z;

    viewMatrix[3][0] = -u.x * camera.x - u.y * camera.y - u.z * camera.z;
    viewMatrix[3][1] = -v.x * camera.x - v.y * camera.y - v.z * camera.z;
    viewMatrix[3][2] = -n.x * camera.x - n.y * camera.y - n.z * camera.z;

    // viewMatrix = glm::lookAt(camera,target,up);

    return viewMatrix;
}

inline glm::mat4 viewport(float _x, float _y, float _n, float _f, float width,
                          float height) {
    glm::mat4 viewPortMatrix(1.0f);
    viewPortMatrix[0][0] = width / 2.0f;
    viewPortMatrix[3][0] = _x + width / 2.0f;
    viewPortMatrix[1][1] = -height / 2.0f;
    viewPortMatrix[3][1] = _y + height / 2.0f;
    viewPortMatrix[2][2] = (_f - _n) / 2.0f;
    viewPortMatrix[3][2] = (_n + _f) / 2.0f; //(_n + _f) / 2.0f;
    return viewPortMatrix;
}

inline glm::mat4 scale(glm::vec3 scalePara) {
    glm::mat4 trans = glm::mat4(1.0);
    for (int i = 0; i < 3; i++) {
        trans[i][i] *= scalePara[i];
    }
    return trans;
}

inline glm::mat4 translate(glm::vec3 translatePara) {
    glm::mat4 trans = glm::mat4(1.0);
    for (int i = 0; i < 3; i++) {
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
    glm::mat4 backTrans = mth::translate(startPos);

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

} // namespace Fallment::mth

#endif